// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
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

#if HAS_UDEV_AND_LIBUSB_SUPPORT
  constexpr bool hasUdevAndLibusbSupport = true;
#else
  constexpr bool hasUdevAndLibusbSupport = false;
#endif


class PortSetupImpl
{
 public:

  void findUdevUsbSerialPort(const PortInfo & portInfo);
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


void PortSetupImpl::findUdevUsbSerialPort([[maybe_unused]] const PortInfo & portInfo)
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

/// \todo remove maybe_unused once libraries support ok
void PortSetupImpl::configureMoxaUPort_1250_1450_1650_UsingUserspaceUsb([[maybe_unused]] const Interface & interface)
{
  assert( hasUdevUsbSerialPort() );

  using namespace std::chrono_literals;

#if HAS_UDEV_AND_LIBUSB_SUPPORT
  auto usbContext = std::make_shared<Mdt::Usb::Context>();

  Mdt::Usb::DeviceEnumerator deviceEnumerator(usbContext);
  const Mdt::Usb::LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();

  libusb_device *device = deviceList.findLibusbDeviceOnBusWithAddress( mUdevUsbSerialPort->usbBusNumber(), mUdevUsbSerialPort->usbDeviceAddress() );
  if(device == nullptr){
    QString msg = PortSetup::tr("failed to configure Moxa UPort interface: no USB device found at bus %1 device address %2")
                  .arg( mUdevUsbSerialPort->usbBusNumber() )
                  .arg( mUdevUsbSerialPort->usbDeviceAddress() );
    throw PortSetupError(msg);
  }

  try{
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
  }catch(const Mdt::Usb::LibusbRuntimeError & error){
    QString msg = PortSetup::tr("failed to configure Moxa UPort interface attached at UBS bus %1 device address %2: %3")
                  .arg( mUdevUsbSerialPort->usbBusNumber() )
                  .arg( mUdevUsbSerialPort->usbDeviceAddress() )
                  .arg( error.text() );
    PortSetupError psError(msg);
    if(error.errorCode() == LIBUSB_ERROR_ACCESS){
      QString informativeText = PortSetup::tr(
        "USB access to the device is denied"
      );
      psError.setInformativeText(informativeText);
      QString detailedText = PortSetup::tr(
        "To have direct access to the USB device, some UDev rules are probably required.\n"
        "Check if a package is avilable for your distribution on https://gitlab.com/scandyna/mdtusb."
      );
      psError.setDetailedText(detailedText);
    }
    throw psError;
  }
#endif // HAS_UDEV_AND_LIBUSB_SUPPORT
}

PortSetup::PortSetup(QObject *parent)
 : QObject(parent),
   mImpl( std::make_unique<PortSetupImpl>() )
{
}

PortSetup::~PortSetup() noexcept = default;

void PortSetup::fetchPortInformations(const PortInfo & portInfo)
{
  assert(mImpl != nullptr);
  assert( !portInfo.systemLocation().isEmpty() );

  if( isMoxaUPort_1250_1450_1650(portInfo) && hasUdevAndLibusbSupport ){
    mImpl->findUdevUsbSerialPort(portInfo);
  }
}

bool PortSetup::shouldConfigureInterfaceBeforeOpenPort() const
{
  assert(mImpl != nullptr);

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

void PortSetup::configureInterfaceBeforeOpenPortIfRequired(const Interface & interface)
{
  assert(mImpl != nullptr);

  if( !interface.isConfigurable() ){
    return;
  }
  if( shouldConfigureInterfaceBeforeOpenPort() ){
    configureInterfaceBeforeOpenPort(interface);
  }
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

void PortSetup::configureInterfaceOncePortOpenIfRequired(const Interface & interface, QSerialPort & port)
{
  assert( port.isOpen() );
  assert(mImpl != nullptr);

  if( !interface.isConfigurable() ){
    return;
  }
  if( shouldConfigureInterfaceBeforeOpenPort() ){
    return;
  }
  configureInterfaceOncePortOpen(interface, port);
}

}} // namespace Mdt{ namespace SerialPort{
