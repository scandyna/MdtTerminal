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

#include "Mdt/SerialPort/Unix/FileStatus.h"
#include "Mdt/SerialPort/Unix/FileStatusFileType.h"
#include "Mdt/SerialPort/Unix/UdevContext.h"
#include "Mdt/SerialPort/Unix/UdevDevice.h"

#include "Mdt/SerialPort/UsbVendorIdProductId.h"

#include "Mdt/SerialPort/Unix/UdevBusDevicePortNumber.h"

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

libusb_device *findDeviceOnBusWithAddress(const Mdt::Usb::LibusbDeviceList & deviceList, uint8_t busNumber, uint8_t deviceAddress)
{
  for(size_t i=0; i < deviceList.count(); ++i){
    libusb_device *device = deviceList.libusbDevicePointerAt(i);
    if( (libusb_get_bus_number(device) == busNumber) && (libusb_get_device_address(device) == deviceAddress) ){
      return device;
    }
  }

  return nullptr;
}

libusb_device_handle *openDeviceOnBusWithAddress(std::shared_ptr<Mdt::Usb::Context> context, uint8_t busNumber, uint8_t deviceAddress)
{
  assert(context != nullptr);

  Mdt::Usb::DeviceEnumerator deviceEnumerator(context);

  Mdt::Usb::LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();

  libusb_device *device = findDeviceOnBusWithAddress(deviceList, busNumber, deviceAddress);
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
  using Mdt::SerialPort::Unix::FileStatus;

  // struct stat st;
  // int ret = stat("/dev/ttyUSB1", &st);
  // if(ret < 0){
  //   qDebug() << "Failed to stat: " << errno;
  //   return;
  // }
  // 
  // qDebug() << " st_dev" << st.st_dev;
  // qDebug() << " st_rdev" << st.st_rdev;

  const auto fileStatus = FileStatus::fromPath("/dev/ttyUSB1");

  qDebug() << " device: " << fileStatus.representedDeviceId();
  qDebug() << "  is block: " << fileStatus.isBlockDevice();
  qDebug() << "  is char: " << fileStatus.isCharacterDevice();
}

void printUdevDevice(udev_device *device)
{
  using Mdt::SerialPort::Unix::UdevDevice;

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

  // qDebug() << " attr idVendor: " << udev_device_get_sysattr_value(device, "idVendor");
  const auto vid = UdevDevice::getVendorId(device);
  if( vid.has_value() ){
    qDebug() << " - VID: 0x" << QString::number(*vid, 16) << " (" << *vid << ")";
  }

  // qDebug() << " attr idProduct: " << udev_device_get_sysattr_value(device, "idProduct");
  const auto pid = UdevDevice::getProductId(device);
  if( vid.has_value() ){
    qDebug() << " - PID: 0x" << QString::number(*pid, 16) << " (" << *pid << ")";
  }

  // qDebug() << " attr busnum: " << udev_device_get_sysattr_value(device, "busnum");
  const auto busNumber = UdevDevice::getBusNumber(device);
  if( busNumber.has_value() ){
    qDebug() << " - bus: " << *busNumber;
  }

  // qDebug() << " attr devnum: " << udev_device_get_sysattr_value(device, "devnum");
  const auto deviceNumber = UdevDevice::getDeviceNumber(device);
  if( deviceNumber.has_value() ){
    qDebug() << " - device " << *deviceNumber;
  }

  // qDebug() << " attr port_number: " << udev_device_get_sysattr_value(device, "port_number");
  const auto portNumber = UdevDevice::getPortNumber(device);
  if( portNumber.has_value() ){
    qDebug() << " - port number " << *portNumber;
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


  /*! \brief Walk an Udev tree branch direction to root
   *
   * Calls the UnaryFunc \a f for each device node
   * during the walk, including the given start node \a device ,
   * as long as \a pred returns true.
   *
   * \note \a pred is called before \a f .
   *
   * UnaryFunc should be of the for:
   * \code
   * void f(udev_device *device);
   * \endcode
   *
   * UnaryPred should be of the form:
   * \code
   * bool p(udev_device *device);
   * \endcode
   *
   * The given device pointer will never be null
   * while calling \a p of \a f .
   */
  // template<typename UnaryFunc, typename UnaryPred>
  // void walkUdevTreeToRootWhile(const Mdt::SerialPort::Unix::UdevDevice & device, UnaryFunc f, UnaryPred p)
  // {
  //   udev_device *devicePtr = device.nativePointer();
  //   if(devicePtr == nullptr){
  //     return;
  //   }
  //   if( !p(devicePtr) ){
  //     return;
  //   }
  // 
  //   f(devicePtr);
  // 
  //   for( udev_device *parent = udev_device_get_parent(devicePtr) ; parent != nullptr ; parent = udev_device_get_parent(parent) ){
  //     if( !p(parent) ){
  //       return;
  //     }
  //     f(parent);
  //   }
  // }



  /*! \brief Check if given device matches given vendor ID and product ID
   */
  // bool deviceMatchesVidPid(udev_device *device, const UsbVendorIdProductId & vidPid) noexcept
  // {
  //   using Mdt::SerialPort::Unix::UdevDevice;
  // 
  //   assert(device != nullptr);
  // 
  //   const auto deviceVidPid = UdevDevice::getVendorIdProductId(device);
  //   if( !deviceVidPid.has_value() ){
  //     return false;
  //   }
  // 
  //   return *deviceVidPid == vidPid;
  // }

  /*! \brief Find the bus, device and port number
   */
//   std::optional<UdevBusDevicePortNumber> findBusDevicePortNumber(const Mdt::SerialPort::Unix::UdevDevice & device, const UsbVendorIdProductId & vidPid)
//   {
//     UdevBusDevicePortNumber result;
//     bool found = false;
// 
//     /*
//      * We start at a leaf of the device tree.
//      * Walk up until we find the expected device.
//      * If we walk more, we will probably en up to a PCI controller.
//      * On the road, we also will get the port number of the device.
//      */
// 
//     const auto f = [&result](udev_device *devicePtr)
//     {
//       using Mdt::SerialPort::Unix::UdevDevice;
// 
//       printUdevDevice(devicePtr);
//       
//       const auto bus = UdevDevice::getBusNumber(devicePtr);
//       if( bus.has_value() ){
//         result.busNumber = *bus;
//       }
// 
//       const auto devnum = UdevDevice::getDeviceNumber(devicePtr);
//       if( devnum.has_value() ){
//         result.deviceNumber = *devnum;
//       }
// 
//       const auto port = UdevDevice::getPortNumber(devicePtr);
//       if( port.has_value() ){
//         result.portNumber = *port;
//       }
//     };
// 
//     const auto pred = [vidPid, &found](udev_device *devicePtr) -> bool
//     {
//       using Mdt::SerialPort::Unix::UdevDevice;
// 
//       found =  UdevDevice::deviceMatchesVidPid(devicePtr, vidPid);
//       return found;
//     };
// 
//     walkUdevTreeToRootUntil(device, f, pred);
// 
//     // if( !isComplete(result) ){
//     //   return {};
//     // }
// 
//     if( !found ){
//       return {};
//     }
// 
//     return result;
//   }
// 
  /*! \brief Find the bus, device and port number for given path
   *
   * Example:
   * Imagine we have 2 Moxa UPort 1250 attached to the system.
   * - /dev/ttyUSB0 : bus 1, device 4, port number 0  (VID: 0x110a, PID: 0x1250)
   * - /dev/ttyUSB1 : bus 1, device 4, port number 1  (VID: 0x110a, PID: 0x1250)
   * - /dev/ttyUSB2 : bus 2, device 3, port number 0  (VID: 0x110a, PID: 0x1250)
   * - /dev/ttyUSB3 : bus 2, device 3, port number 1  (VID: 0x110a, PID: 0x1250)
   *
   * Here, the VID and PID of the device is the same for both.
   * If we want, f.ex., set the interface of ttyUSB1 to RS-422 with an USB control transfert,
   * we need to know the bus and device (address) to differentiate which device to configure,
   * and also the port number of the device.
   *
   * \note The VID and PID is required because of the way the libudev API is made.
   * See implementation for more details.
   *
   * \pre 
   * \exception 
   */
  // std::optional<UdevBusDevicePortNumber> findBusDevicePortNumberFromPath(const std::filesystem::path & path, const UsbVendorIdProductId & vidPid)
  // {
  //   using Mdt::SerialPort::Unix::UdevDevice;
  //   using Mdt::SerialPort::Unix::FileStatus;
  // 
  //   const auto fileStatus = FileStatus::fromPath(path);
  // 
  //   const auto udevContext = std::make_shared<Mdt::SerialPort::Unix::UdevContext>();
  // 
  //   auto device = UdevDevice::from_devnum( udevContext, fileStatus.fileType(), fileStatus.representedDeviceId() );
  // 
  //   return findBusDevicePortNumber(device, vidPid);
  // }

TEST_CASE("libudev_sandbox")
{
  using Mdt::SerialPort::Unix::UdevDevice;
  using Mdt::SerialPort::Unix::FileStatus;

  const auto udevContext = std::make_shared<Mdt::SerialPort::Unix::UdevContext>();
  // udev *udevContext = udev_new();
  // assert(udevContext != nullptr);

  /** \todo see:
   * https://stackoverflow.com/questions/40215880/libudev-get-devnum-for-specific-tty-in-c
   * https://stackoverflow.com/questions/20249418/find-bus-number-and-device-number-with-device-file-symlink/20341112#20341112
   * https://manpages.debian.org/stretch-backports/libudev-dev/udev_device_get_property_value.3.en.html
   */

  const std::filesystem::path devicePath = "/dev/ttyUSB1";
  const auto fileStatus = FileStatus::fromPath(devicePath);

  // char deviceTypeChar = UdevDevice::deviceTypeCharFromFileType( fileStatus.fileType() );
  // if( fileStatus.isBlockDevice() ){
  //   deviceTypeChar = 'b';
  // }else if( fileStatus.isCharacterDevice() ){
  //   deviceTypeChar = 'c';
  // }
  // if(deviceTypeChar == '\0'){
  //   qDebug() << "device " << devicePath.string().c_str() << " is neither a block or character device";
  //   return;
  // }

  qDebug() << " print tree - OLD ************** ";

  auto device2 = UdevDevice::from_devnum( udevContext, fileStatus.fileType(), fileStatus.representedDeviceId() );

  /*
   * We start at a leaf of the device tree.
   * Walk up until we find the expected device.
   * If we walk more, we will probably en up to a PCI controller.
   * On the road, we also will get the port number of the device.
   */

  udev_device *device = device2.nativePointer();
  // udev_device *device = udev_device_new_from_devnum( udevContext->nativePointer(), deviceTypeChar, fileStatus.representedDeviceId() );
  // udev_device *device = udev_device_new_from_devnum(udevContext, 'c', 48129);
  // udev_device *device = udev_device_new_from_syspath(udevContext, "/dev/ttyUSB0");
  // if(device == nullptr){
  //   qDebug() << "Failed to get UDEV device: " << errno;
  //   return;
  // }

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

  // qDebug() << " print tree - walkUdevTreeToRoot ************** ";
  // 
  // walkUdevTreeToRoot(device2, printUdevDevice);

  // udev_device_unref(device);
  // udev_unref(udevContext);

  // qDebug() << " +-+-+ search device ======== ...";

  // const auto busDevicePortNumber = findBusDevicePortNumberFromPath(devicePath, {0x110A, 0x1250});
  // if( busDevicePortNumber.has_value() ){
  //   qDebug() << "+++ found .......... bus: " << busDevicePortNumber->busNumber << " - device: " << busDevicePortNumber->deviceNumber << " - port: " << busDevicePortNumber->portNumber;
  // }
}

void setMoxaUportInterfaceNumber(libusb_device_handle *deviceHandle, uint16_t portNumber, uint16_t interfaceNumber)
{
  assert(deviceHandle != nullptr);

  /// \todo portnum vs ifacenum !

  constexpr uint8_t RQ_VENDOR_SET_INTERFACE = 0x10;

  uint8_t bmRequestType = LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE;
  uint8_t bRequest = RQ_VENDOR_SET_INTERFACE;
  uint16_t wValue = interfaceNumber;
  uint16_t wIndex = portNumber;
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

  // libusb_device_handle *deviceHandle = openFirstDeviceWithVidAndPid(context, 0x110A, 0x1250);
  libusb_device_handle *deviceHandle = openDeviceOnBusWithAddress(context, 1, 6);
  if(deviceHandle == nullptr){
    qDebug() << "device find/open error";
    return;
  }

  qDebug() << " -> open device :)";

  /// \todo maybe detach kernel driver


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

TEST_CASE("setup_uport_sandbox")
{
  const std::filesystem::path devicePath = "/dev/ttyUSB0";

  const auto busDevicePortNumber = Mdt::SerialPort::Unix::findBusDevicePortNumberFromPath(devicePath, {0x110A, 0x1250});
  if( !busDevicePortNumber.has_value() ){
    qDebug() << "-> could not find device..";
    return;
  }

  auto context = std::make_shared<Mdt::Usb::Context>();

  libusb_device_handle *deviceHandle = openDeviceOnBusWithAddress(context, busDevicePortNumber->busNumber, busDevicePortNumber->deviceNumber);
  if(deviceHandle == nullptr){
    qDebug() << "device find/open error";
    return;
  }

  qDebug() << " -> open device :)";

  setMoxaUportInterfaceNumber(deviceHandle, busDevicePortNumber->portNumber, 2);

  libusb_close(deviceHandle);
}
