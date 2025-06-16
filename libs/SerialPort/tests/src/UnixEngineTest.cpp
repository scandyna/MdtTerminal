// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Unix/UnixEngine.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

#include <QObject>

/** \todo Just a sanbox - will not work on CI
 *
 * libusb dev is probably not installed on CI images, and must not be !
 * Later, we should use the Conan generated CMake files
 * for proper integration.
 */
#include <libusb.h>

#include "Mdt/Usb/Context.h"
#include "Mdt/Usb/LibusbDeviceList.h"
#include "Mdt/Usb/DeviceEnumerator.h"
#include "Mdt/Usb/DeviceDescriptor.h"
#include "Mdt/Usb/ConfigDescriptor.h"

#include "Mdt/Usb/LibusbError.h"

#include <memory>
#include <cassert>

#include <QDebug>

#include <libudev.h>

#include "Mdt/SerialPort/Unix/FileStatus.h"
#include "Mdt/SerialPort/Unix/FileStatusFileType.h"
#include "Mdt/SerialPort/Unix/UdevContext.h"
#include "Mdt/SerialPort/Unix/UdevDevice.h"

#include "Mdt/SerialPort/UsbVendorIdProductId.h"

#include "Mdt/SerialPort/Unix/UdevBusDevicePortNumber.h"

#include "Mdt/Usb/DeviceHandle.h"

#include <QSerialPort>

using namespace Mdt::SerialPort;


void printDeviceDescriptor(const Mdt::Usb::DeviceDescriptor & descriptor)
{
  qDebug() << "Device VID: " << descriptor.idVendor() << ", PID: " << descriptor.idProduct();
}


void printEndpointDescriptor(const Mdt::Usb::EndpointDescriptor & descriptor)
{
  qDebug() << "   Endpoint:";
  qDebug() << "    Address:" << descriptor.bEndpointAddress();
}

void printInterfaceDescriptor(const Mdt::Usb::InterfaceDescriptor & descriptor)
{
  qDebug() << "  Interface setting:";
  for(uint8_t i=0; i < descriptor.bNumEndpoints(); ++i){
    printEndpointDescriptor( descriptor.endpointAt(i) );
  }
}

void printInterface(const Mdt::Usb::Interface & interface)
{
  qDebug() << " Interface:";
  for(size_t i=0; i < interface.alternateSettingsCount(); ++i){
    printInterfaceDescriptor( interface.alternateSettingAt(i) );
  }
}

void printConfigDescriptor(const Mdt::Usb::ConfigDescriptor & descriptor)
{
  qDebug() << "Config: ";
  for(uint8_t i=0; i < descriptor.bNumInterfaces(); ++i){
    printInterface( descriptor.interfaceAt(i) );
  }
}


  /*! \brief Couple of USB bus number and device address
   */
  struct UsbBusNumberDeviceAddress
  {
    /*! \brief Bus number
     *
     * This bus number matche libusb_get_bus_number()
     * and the Udev busnum attribute.
     */
    uint8_t busNumber = 0;
  
    /*! \brief Device address
     *
     * This device address matches libusb_get_device_address()
     * and the Udev devnum attribute.
     */
    uint8_t deviceAddress = 0;
  };
  


  /*! \brief Setup packet for control transfers
   *
   * Contains the same members as libusb_control_setup.
   * This ControlSetup is available to avoid confusions with libusb_control_setup
   * (see below).
   *
   * In the libusb API, the multi-byte control setup fields (wValue, wIndex and wLength)
   * must be given in the endianness of the USB bus (little-endian).
   *
   * This ControlSetup excepts host endianness.
   * libusb helpers will be used to do the conversions if needed.
   *
   * \sa https://libusb.sourceforge.io/api-1.0/structlibusb__control__setup.html
   * \sa https://libusb.sourceforge.io/api-1.0/group__libusb__asyncio.html
   * \sa USB 3.2 specification §9.3
   */
  struct ControlSetup
  {
    uint8_t bmRequestType = 0;
    uint8_t bRequest = 0;
    uint16_t wValue = 0;
    uint16_t wIndex = 0;
    uint16_t wLength = 0;

    /// \todo use https://www.en.cppreference.com/w/cpp/utility/bitset.html

    /*! \brief
     *
     * Set bit .. of bmRequestType ...
     */
    constexpr
    void setDataTransferDirectionHostToDevice() noexcept
    {
    }

    /*! \brief
     */
    constexpr
    void setDataTransferDirectionDeviceToHost() noexcept
    {
    }

  };

  /*! \brief Perform a (synchronous) USB control transfer
   *
   * This is a helper around libusb_control_transfer()
   *
   * \exception Maybe none here !
   * 
   * \sa https://libusb.sourceforge.io/api-1.0/group__libusb__syncio.html
   *
   * \todo timeout std::chrono
   *
   * \todo data should be something safer - span ? later..
   */
  void controlTransfer(const ControlSetup & setup, unsigned char *data)
  {
  }

  /*! \brief Perform a (synchronous) USB control transfer
   *
   * This is a helper around controlTransfer() for requests
   * having no data exchange with the device.
   *
   * \pre the wLength filed of \a setup must be 0
   * \sa controlTransfer()
   */
  void controlTransferWithoutData(const ControlSetup & setup)
  {
  }

void setMoxaUportInterfaceNumber(Mdt::Usb::DeviceHandle &deviceHandle, uint16_t portNumber, uint16_t interfaceNumber)
{
  assert(deviceHandle.libusbHandle() != nullptr);

  /// \todo portnum vs ifacenum ! + maybe check its a Moxa UPort ?

  constexpr uint8_t RQ_VENDOR_SET_INTERFACE = 0x10;

  uint8_t bmRequestType = LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE;
  uint8_t bRequest = RQ_VENDOR_SET_INTERFACE;
  uint16_t wValue = interfaceNumber;
  uint16_t wIndex = portNumber;
  unsigned char fakeData;
  uint16_t wLength = 0;
  unsigned int timeout = 100;

  int ret = libusb_control_transfer(
    deviceHandle.libusbHandle(),
    bmRequestType,
    bRequest,
    wValue,
    wIndex,
    &fakeData,
    wLength,
    timeout
  );
  if(ret != 0){
    qDebug() << "Control transfer failed: " << ret;
  }

}

TEST_CASE("libusb_sandbox")
{
  auto context = std::make_shared<Mdt::Usb::Context>();

  Mdt::Usb::DeviceEnumerator deviceEnumerator(context);
  Mdt::Usb::LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();

  libusb_device *device = deviceList.findFirstLibusbDeviceWithVidAndPid(0x110A, 0x1250);
  if(device == nullptr){
    return;
  }

  // const auto deviceDescriptor = Mdt::Usb::DeviceDescriptor::fromLibusbDevicePointer(device);
  const auto deviceDescriptor = Mdt::Usb::DeviceDescriptor::fromLibusbDevicePointer(device);
  const auto configDescriptor = Mdt::Usb::ConfigDescriptor::activeConfigFromLibusbDevicePointer(device);

  printDeviceDescriptor(deviceDescriptor);
  printConfigDescriptor(configDescriptor);

  device = deviceList.findLibusbDeviceOnBusWithAddress(1, 6);
  if(device == nullptr){
    qDebug() << "device not found..";
    return;
  }

  auto deviceHandle = Mdt::Usb::DeviceHandle::open(device);

  qDebug() << " -> open device :)";
}

TEST_CASE("setup_uport_sandbox")
{
  const std::filesystem::path devicePath = "/dev/ttyUSB0";

  const auto busDevicePortNumber = Mdt::SerialPort::Unix::findBusDevicePortNumberFromPath(devicePath, {0x110A, 0x1250});
  if( !busDevicePortNumber.has_value() ){
    qDebug() << "-> could not find device..";
    return;
  }

  auto context = std::make_shared<Mdt::Usb::Context>();

  Mdt::Usb::DeviceEnumerator deviceEnumerator(context);
  Mdt::Usb::LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();

  libusb_device *device = deviceList.findLibusbDeviceOnBusWithAddress( busDevicePortNumber->busNumber, busDevicePortNumber->deviceNumber );
  if(device == nullptr){
    qDebug() << "device not found...";
    return;
  }

  auto deviceHandle = Mdt::Usb::DeviceHandle::open(device);

  qDebug() << " -> open device :)";

  setMoxaUportInterfaceNumber(deviceHandle, busDevicePortNumber->portNumber, 2);
}
