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

#include <memory>
#include <cassert>

#include <QDebug>

#include <libudev.h>

#include "Mdt/SerialPort/Unix/UnixFileStatus.h"

#include <QSerialPort>

using namespace Mdt::SerialPort;


  /*! \brief
   *
   * \todo We have a lifetime issue with the libusb_device (opac struct) pointer.
   * Should be a separate thing ?
   */
  // class DeviceDescriptor
  // {
  // };


  /*! \brief
   */
  // class DeviceDescriptorAndPointer
  // {
  //  public:
  // 
  //   const DeviceDescriptor & descriptor() const noexcept
  //   {
  //   }
  // 
  //   /*! \brief
  //    *
  //    * \warning The returned pointer is only valid as long as the device list is.
  //    * \sa DeviceList
  //    */
  //   libusb_device *libUsbDevicePointer() const
  //   {
  //   }
  // };



  /*! \brief
   */
  // class DeviceHandle
  // {
  //  public:
  // 
  //   static
  //   DeviceHandle openFromDescriptor(const DeviceDescriptor & descriptor);
  // 
  //   // static
  //   // DeviceHandle openDeviceWithVidPidSn()
  //   // {
  //   //   DeviceList deviceList = DeviceListBuilder::scanForAttachedDevices();
  //   // 
  //   //   DeviceDescriptor deviceDescriptor = deviceList.findXy(...);
  //   // 
  //   //   return DeviceHandle::openFromDescriptor(deviceDescriptor);
  //   // }
  // };

libusb_device *findFirstLibusbDeviceWithVidAndPid(const Mdt::Usb::LibusbDeviceList & deviceList, uint16_t vid, uint16_t pid)
{
  using Mdt::Usb::DeviceDescriptor;

  for(size_t i=0; i < deviceList.count(); ++i){
    libusb_device *device = deviceList.libusbDevicePointerAt(i);
    const auto deviceDescriptor = DeviceDescriptor::fromLibusbDevicePointer(device);
    if( (deviceDescriptor.idVendor() == vid) && (deviceDescriptor.idProduct() == pid) ){
      return device;
    }
  }

  return nullptr;
}

// Mdt::Usb::DeviceDescriptor findDeviceDescriptorWithVidAndPid(const Mdt::Usb::LibusbDeviceList & deviceList, uint16_t vid, uint16_t pid)
// {
// }

libusb_device_handle *openFirstDeviceWithVidAndPid(std::shared_ptr<Mdt::Usb::Context> context, uint16_t vid, uint16_t pid)
{
  assert(context != nullptr);

  Mdt::Usb::DeviceEnumerator deviceEnumerator(context);

  Mdt::Usb::LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();

  libusb_device *device = findFirstLibusbDeviceWithVidAndPid(deviceList, vid, pid);
  if(device == nullptr){
    return nullptr;
  }

  libusb_device_handle *handle;
  int ret = libusb_open(device, &handle);
  qDebug() << "libusb_open() ret: " << ret << " - " << libusb_error_name(ret);
  if(ret != 0){
    return nullptr;
  }
  /// \todo error handling
  return handle;

  // for(size_t i=0; i < deviceList.count(); ++i){
  //   libusb_device_descriptor deviceDescriptor;
  //   int ret = libusb_get_device_descriptor(deviceList.libusbDevicePointerAt(i), &deviceDescriptor);
  //   /// \todo error handling
  //   if( (deviceDescriptor.idVendor == vid) && (deviceDescriptor.idProduct == pid) ){
  //     libusb_device_handle *handle;
  //     ret = libusb_open(deviceList.libusbDevicePointerAt(i), &handle);
  //     qDebug() << "libusb_open() ret: " << ret << " - " << libusb_error_name(ret);
  //     if(ret != 0){
  //       return nullptr;
  //     }
  //     /// \todo error handling
  //     return handle;
  //   }
  // }
  // 
  // return nullptr;
}


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

// libusb_wrap_sys_device() available starting from libusb 1.0.23
// TEST_CASE("libusb_wrap_sys_device_sandbox")
// {
//   QSerialPort serialPort;
//   serialPort.setPortName("/dev/ttyUSB0");
//   if( !serialPort.open(QIODevice::ReadWrite) ){
//     qDebug() << "Failed to open serial port: " << serialPort.errorString();
//     return;
//   }
// 
//   auto usbContext = std::make_shared<Mdt::Usb::Context>();
// 
//   libusb_device_handle *handle;
//   int ret = libusb_wrap_sys_device(usbContext->libusbContext(), serialPort.handle(), &handle);
//   if(ret != 0){
//     qDebug() << "Failed to wrap port to libusb";
//     return;
//   }
// 
//   serialPort.close();
// }


TEST_CASE("stat_sandbox")
{
  struct stat st;
  int ret = stat("/dev/ttyUSB1", &st);
  if(ret < 0){
    qDebug() << "Failed to stat: " << errno;
    return;
  }

  qDebug() << " st_dev" << st.st_dev;
  qDebug() << " st_rdev" << st.st_rdev;
}

void printUdevDevice(udev_device *device)
{
  assert(device != nullptr);

  qDebug() << "sysname: " << udev_device_get_sysname(device);
  qDebug() << "type: " << udev_device_get_devtype(device);
  qDebug() << "subsystem: " << udev_device_get_subsystem(device);

  // qDebug() << "property KERNEL: " << udev_device_get_property_value(device, "KERNEL");
  // qDebug() << "attr KERNEL: " << udev_device_get_sysattr_value(device, "KERNEL");

  // qDebug() << "has tag: " <<  udev_device_has_tag(device, "");
  // qDebug() << "has tag busnum: " <<  udev_device_has_tag(device, "busnum");
  // qDebug() << "has tag devnum: " <<  udev_device_has_tag(device, "devnum");
  // 
  // qDebug() << "property busnum: " << udev_device_get_property_value(device, "busnum");
  // qDebug() << "property devnum: " << udev_device_get_property_value(device, "devnum");

  qDebug() << " attr manufacturer: " << udev_device_get_sysattr_value(device, "manufacturer");
  qDebug() << " attr product: " << udev_device_get_sysattr_value(device, "product");

  qDebug() << " attr busnum: " << udev_device_get_sysattr_value(device, "busnum");
  qDebug() << " attr devnum: " << udev_device_get_sysattr_value(device, "devnum");
  qDebug() << " attr port_number: " << udev_device_get_sysattr_value(device, "port_number");
}

TEST_CASE("libudev_sandbox")
{
  udev *udevContext = udev_new();
  assert(udevContext != nullptr);

  /** \todo see:
   * https://stackoverflow.com/questions/40215880/libudev-get-devnum-for-specific-tty-in-c
   * https://stackoverflow.com/questions/20249418/find-bus-number-and-device-number-with-device-file-symlink/20341112#20341112
   * https://manpages.debian.org/stretch-backports/libudev-dev/udev_device_get_property_value.3.en.html
   */

  /*
   * We start at a leaf of the device tree.
   * Walk up until we find the expected device.
   * If we walk more, we will probably en up to a PCI controller.
   * On the road, we also will get the port number of the device.
   */

  udev_device *device = udev_device_new_from_devnum(udevContext, 'c', 48129);
  // udev_device *device = udev_device_new_from_syspath(udevContext, "/dev/ttyUSB0");
  if(device == nullptr){
    qDebug() << "Failed to get UDEV device: " << errno;
    return;
  }

  printUdevDevice(device);

  // printUdevDevice(parent);

  // parent = udev_device_get_parent(parent);
  // printUdevDevice(parent);
  // parent = udev_device_get_parent(parent);
  // printUdevDevice(parent);
  // parent = udev_device_get_parent(parent);
  // printUdevDevice(parent);
  // parent = udev_device_get_parent(parent);
  // printUdevDevice(parent);

  for( udev_device *parent = udev_device_get_parent(device) ; parent != nullptr ; parent = udev_device_get_parent(parent) ){
    printUdevDevice(parent);
  }

  udev_device_unref(device);
  udev_unref(udevContext);
}

TEST_CASE("libusb_sandbox")
{
  auto context = std::make_shared<Mdt::Usb::Context>();

  Mdt::Usb::DeviceEnumerator deviceEnumerator(context);
  Mdt::Usb::LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();

  libusb_device *device = findFirstLibusbDeviceWithVidAndPid(deviceList, 0x110A, 0x1250);
  if(device == nullptr){
    return;
  }

  // const auto deviceDescriptor = Mdt::Usb::DeviceDescriptor::fromLibusbDevicePointer(device);
  const auto deviceDescriptor = Mdt::Usb::DeviceDescriptor::fromLibusbDevicePointer(device);
  const auto configDescriptor = Mdt::Usb::ConfigDescriptor::activeConfigFromLibusbDevicePointer(device);

  printDeviceDescriptor(deviceDescriptor);
  printConfigDescriptor(configDescriptor);

  libusb_device_handle *deviceHandle = openFirstDeviceWithVidAndPid(context, 0x110A, 0x1250);
  if(deviceHandle == nullptr){
    qDebug() << "device find/open error";
    return;
  }

  qDebug() << " -> open device :)";

  /// \todo maybe detach kernel driver

  constexpr uint8_t RQ_VENDOR_SET_INTERFACE = 0x10;

  uint8_t bmRequestType = LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE;
  uint8_t bRequest = RQ_VENDOR_SET_INTERFACE;
  uint16_t wValue = 1;
  uint16_t wIndex = 0;
  unsigned char fakeData;
  uint16_t wLength = 0;
  unsigned int timeout = 100;

  int ret = libusb_control_transfer(
    deviceHandle,
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

  libusb_close(deviceHandle);

  // DeviceEnumerator deviceEnumerator(context);
  // 
  // LibUsbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();
  // 
  // for(size_t i=0; i < deviceList.count(); ++i){
  //   qDebug() << " device at " << i << "...";
  //   libusb_device_descriptor deviceDescriptor;
  //   int ret = libusb_get_device_descriptor(deviceList.devicePointerAt(i), &deviceDescriptor);
  //   /// \todo error handling
  //   qDebug() << "VID: " << deviceDescriptor.idVendor << " , PID: " << deviceDescriptor.idProduct;
  // }

  // libusb_context *usbContext = nullptr;

  /// \todo Once 1.0.27 available, use libusb_init_context() (conan provides 1.0.26 in 2025)
  // int ret = libusb_init(&usbContext);
  /// \todo error handling
  // assert(ret == 0);

  // libusb_exit(usbContext);
}
