// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/LibusbDeviceList.h"
#include "Mdt/Usb/DeviceEnumerator.h"
#include "Mdt/Usb/DeviceDescriptor.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("findFirstLibusbDeviceWithVidAndPid")
{
  auto context = std::make_shared<Context>();
  DeviceEnumerator deviceEnumerator(context);
  LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();
  REQUIRE( deviceList.count() > 0 );

  SECTION("existing device")
  {
    const auto deviceDescriptor = DeviceDescriptor::fromLibusbDevicePointer( deviceList.libusbDevicePointerAt(0) );

    libusb_device *device = deviceList.findFirstLibusbDeviceWithVidAndPid( deviceDescriptor.idVendor(), deviceDescriptor.idProduct() );

    CHECK( device != nullptr );
  }

  SECTION("None existing device")
  {
    libusb_device *device = deviceList.findFirstLibusbDeviceWithVidAndPid(0xffff, 0xffff);

    CHECK( device == nullptr );
  }
}

TEST_CASE("findLibusbDeviceOnBusWithAddress")
{
  auto context = std::make_shared<Context>();
  DeviceEnumerator deviceEnumerator(context);
  LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();
  REQUIRE( deviceList.count() > 0 );

  SECTION("existing device")
  {
    libusb_device *device = deviceList.libusbDevicePointerAt(0);
    uint8_t bus = libusb_get_bus_number(device);
    uint8_t deviceAddress = libusb_get_device_address(device);

    device = deviceList.findLibusbDeviceOnBusWithAddress(bus, deviceAddress);

    CHECK( device != nullptr );
  }

  SECTION("None existing device")
  {
    libusb_device *device = deviceList.findLibusbDeviceOnBusWithAddress(0xff, 0xff);

    CHECK( device == nullptr );
  }
}
