// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/DeviceDescriptor.h"
#include "Mdt/Usb/ConfigDescriptor.h"
#include "Mdt/Usb/Context.h"
#include "Mdt/Usb/DeviceEnumerator.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("DeviceDescriptor_fromLibusbDevicePointer")
{
  auto context = std::make_shared<Context>();
  DeviceEnumerator deviceEnumerator(context);

  LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();
  REQUIRE( deviceList.count() > 0 );

  const auto deviceDescriptor = DeviceDescriptor::fromLibusbDevicePointer( deviceList.libusbDevicePointerAt(0) );

  CHECK( deviceDescriptor.libusbDescriptor().idProduct != 0 );
}

TEST_CASE("ConfigDescriptor_activeConfigFromLibusbDevicePointer")
{
  auto context = std::make_shared<Context>();
  DeviceEnumerator deviceEnumerator(context);

  LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();
  REQUIRE( deviceList.count() > 0 );

  const auto configDescriptor = ConfigDescriptor::activeConfigFromLibusbDevicePointer( deviceList.libusbDevicePointerAt(0) );

  CHECK( configDescriptor.bNumInterfaces() > 0 );
  CHECK( configDescriptor.bNumInterfaces() < 16 );
}
