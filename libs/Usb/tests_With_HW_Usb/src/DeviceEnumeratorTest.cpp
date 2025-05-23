// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/DeviceEnumerator.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("SimpleTest")
{
  auto context = std::make_shared<Context>();
  DeviceEnumerator deviceEnumerator(context);

  LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();

  CHECK( deviceList.count() > 0 );
}

TEST_CASE("MoveListTest")
{
  auto context = std::make_shared<Context>();
  DeviceEnumerator deviceEnumerator(context);

  LibusbDeviceList deviceList1 = deviceEnumerator.scanForAttachedDevices();
  CHECK( deviceList1.count() > 0 );

  LibusbDeviceList deviceList2 = std::move(deviceList1);

  CHECK( deviceList2.count() > 0 );
  CHECK( deviceList1.count() == 0 );
}
