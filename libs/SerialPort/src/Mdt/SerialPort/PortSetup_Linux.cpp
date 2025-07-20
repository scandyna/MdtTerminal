// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortSetup.h"
#include "FilesystemHelpers.h"
#include "Linux/MoxaUPort.h"
#include <optional>
#include <filesystem>
#include <string>
#include <chrono>
#include <memory>
#include <cassert>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#include <string.h> // memset()


/*! \internal
 *
 * \todo Remove once we have proper libraries support 
 */
#define HAS_UDEV_AND_LIBUSB_SUPPORT true

#if HAS_UDEV_AND_LIBUSB_SUPPORT
  #include "Linux/UdevUsbSerialPort.h"
  #include "Mdt/Usb/Context.h"
  #include "Mdt/Usb/DeviceEnumerator.h"
  #include "Mdt/Usb/LibusbDeviceList.h"
  #include "Mdt/Usb/DeviceHandle.h"
  #include "Mdt/Usb/ControlSetup.h"
  #include "Mdt/Usb/ControlTransfer.h"
#endif // HAS_UDEV_AND_LIBUSB_SUPPORT

namespace Mdt{ namespace SerialPort{

/*! \internal
 *
 * \todo Remove once we have proper libraries support 
 */
constexpr bool hasUdevAndLibusbSupport = HAS_UDEV_AND_LIBUSB_SUPPORT;


class PortSetupImpl
{
 public:

  void findUdevUsbSerialPort(const QSerialPortInfo & portInfo);
  bool hasUdevUsbSerialPort() const noexcept;
  std::string driverName() const noexcept;

  /// \todo Should go to a more specific place
  void configureMoxaUPort_1250_1450_1650_UsingUserspaceUsb(const Interface & interface);

  /// \todo Should go to a more specific place
  void configureMoxaUPort_1250_1450_1650_UsingIoctl();

 private:

#if HAS_UDEV_AND_LIBUSB_SUPPORT
  std::optional<Linux::UdevUsbSerialPort> mUdevUsbSerialPort;
#endif // HAS_UDEV_AND_LIBUSB_SUPPORT
};


void PortSetupImpl::findUdevUsbSerialPort([[maybe_unused]] const QSerialPortInfo & portInfo)
{
#if HAS_UDEV_AND_LIBUSB_SUPPORT
  const std::filesystem::path path = stdFilesystemPathFromQString( portInfo.systemLocation() );
  const UsbVendorIdProductId vidAndPid = PortSetup::usbVendorIdProductIdFromPortInfo(portInfo);

  mUdevUsbSerialPort = Mdt::SerialPort::Linux::findUdevUsbSerialPortFromPath(path, vidAndPid);
#endif // HAS_UDEV_AND_LIBUSB_SUPPORT
}

bool PortSetupImpl::hasUdevUsbSerialPort() const noexcept
{
#if HAS_UDEV_AND_LIBUSB_SUPPORT
  return mUdevUsbSerialPort.has_value();
#else
  return false;
#endif // HAS_UDEV_AND_LIBUSB_SUPPORT
}

std::string PortSetupImpl::driverName() const noexcept
{
  assert( hasUdevUsbSerialPort() );

#if HAS_UDEV_AND_LIBUSB_SUPPORT
  return mUdevUsbSerialPort->driverName();
#else
  return std::string();
#endif // HAS_UDEV_AND_LIBUSB_SUPPORT
}

void PortSetupImpl::configureMoxaUPort_1250_1450_1650_UsingUserspaceUsb(const Interface & interface)
{
  assert( hasUdevUsbSerialPort() );

  using namespace std::chrono_literals;

#if HAS_UDEV_AND_LIBUSB_SUPPORT
  auto usbContext = std::make_shared<Mdt::Usb::Context>();

  Mdt::Usb::DeviceEnumerator deviceEnumerator(usbContext);
  const Mdt::Usb::LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();

  libusb_device *device = deviceList.findLibusbDeviceOnBusWithAddress( mUdevUsbSerialPort->usbBusNumber(), mUdevUsbSerialPort->usbDeviceAddress() );
  if(device == nullptr){
    QString msg = PortSetup::tr("failed to configure Moxa UPort interface: no USB device found at bus %1 device address %1")
                  .arg( mUdevUsbSerialPort->usbBusNumber() )
                  .arg( mUdevUsbSerialPort->usbDeviceAddress() );
    throw PortSetupError(msg);
  }

  auto usbDeviceHandle = Mdt::Usb::DeviceHandle::open(device);
  assert(usbDeviceHandle.libusbHandle() != nullptr);

  using namespace std::chrono_literals;

  constexpr uint8_t RQ_VENDOR_SET_INTERFACE = 0x10;

  Mdt::Usb::ControlSetup cs;

  cs.setRequestType(Mdt::Usb::RequestType::Vendor);
  cs.setRecipient(Mdt::Usb::RequestRecipient::Device);
  cs.setbRequestValue(RQ_VENDOR_SET_INTERFACE);
  cs.setwValueValue( interface.parameterValue() );
  cs.setwIndexValue( mUdevUsbSerialPort->portNumber() );

  Mdt::Usb::controlTransferWithoutData(usbDeviceHandle, cs, 100ms);
#endif // HAS_UDEV_AND_LIBUSB_SUPPORT
}


PortSetup::PortSetup(const QSerialPortInfo & portInfo, QObject *parent)
 : QObject(parent),
   mImpl( std::make_unique<PortSetupImpl>() )
{
  assert( !portInfo.systemLocation().isEmpty() );

  if( isMoxaUPort_1250_1450_1650(portInfo) && hasUdevAndLibusbSupport ){
    mImpl->findUdevUsbSerialPort(portInfo);
  }
}

PortSetup::~PortSetup() noexcept = default;

bool PortSetup::shouldConfigureInterfaceBeforeOpenPort() const
{
  if( !mImpl->hasUdevUsbSerialPort() ){
    return false;
  }

  return Linux::isLinuxMxuportDriver( mImpl->driverName() );
}

void PortSetup::configureInterfaceBeforeOpenPort(const Interface & interface)
{
  assert( mImpl->hasUdevUsbSerialPort() );

  mImpl->configureMoxaUPort_1250_1450_1650_UsingUserspaceUsb(interface);
}

void PortSetup::configureInterfaceOncePortOpen(const Interface & interface, QSerialPort & port)
{
  assert( port.isOpen() );

  int descriptor = port.handle();
  assert(descriptor > -1);

  struct serial_struct serial;
  ::memset( &serial, 0, sizeof(serial) );

  int result = ::ioctl(descriptor, TIOCGSERIAL, &serial);
  if(result == -1){
    const QString msg = tr("configure interface failed while getting serial_struct: %1")
                        .arg( QString::fromLocal8Bit( ::strerror(errno) ) );
    throw PortSetupError(msg);
  }

  serial.port = interface.parameterValue();

  result = ::ioctl(descriptor, TIOCSSERIAL, &serial);
  if(result == -1){
    const QString msg = tr("configure interface failed while setting serial_struct: %1")
                        .arg( QString::fromLocal8Bit( ::strerror(errno) ) );
    throw PortSetupError(msg);
  }
}

}} // namespace Mdt{ namespace SerialPort{
