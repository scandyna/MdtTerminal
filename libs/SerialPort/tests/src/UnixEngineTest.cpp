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

#include <chrono>

#include <QDebug>

#include <libudev.h>

#include "Mdt/SerialPort/Unix/FileStatus.h"
#include "Mdt/SerialPort/Unix/FileStatusFileType.h"
#include "Mdt/SerialPort/Unix/UdevContext.h"
#include "Mdt/SerialPort/Unix/UdevDevice.h"

#include "Mdt/SerialPort/UsbVendorIdProductId.h"

#include "Mdt/SerialPort/Unix/UdevBusDevicePortNumber.h"

#include "Mdt/Usb/DeviceHandle.h"
#include "Mdt/Usb/ControlSetup.h"
#include "Mdt/Usb/ControlTransfer.h"

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
     * This bus number matches libusb_get_bus_number()
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
  


void setMoxaUportInterfaceNumber(Mdt::Usb::DeviceHandle &deviceHandle, uint16_t portNumber, uint16_t interfaceNumber)
{
  assert(deviceHandle.libusbHandle() != nullptr);

  /// \todo portnum vs ifacenum ! + maybe check its a Moxa UPort ?

  using namespace std::chrono_literals;

  constexpr uint8_t RQ_VENDOR_SET_INTERFACE = 0x10;

  Mdt::Usb::ControlSetup cs;

  cs.setRequestType(Mdt::Usb::RequestType::Vendor);
  cs.setRecipient(Mdt::Usb::RequestRecipient::Device);
  cs.setbRequestValue(RQ_VENDOR_SET_INTERFACE);
  cs.setwValueValue(interfaceNumber);
  cs.setwIndexValue(portNumber);

  Mdt::Usb::controlTransferWithoutData(deviceHandle, cs, 100ms);

  return;

  // uint8_t bmRequestType = LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE;
  // uint8_t bRequest = RQ_VENDOR_SET_INTERFACE;
  // uint16_t wValue = interfaceNumber;
  // uint16_t wIndex = portNumber;
  // unsigned char fakeData;
  // uint16_t wLength = 0;
  // unsigned int timeout = 100;
  // 
  // int ret = libusb_control_transfer(
  //   deviceHandle.libusbHandle(),
  //   bmRequestType,
  //   bRequest,
  //   wValue,
  //   wIndex,
  //   &fakeData,
  //   wLength,
  //   timeout
  // );
  // if(ret != 0){
  //   qDebug() << "Control transfer failed: " << ret;
  // }

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

  setMoxaUportInterfaceNumber(deviceHandle, busDevicePortNumber->portNumber, 0);
}
