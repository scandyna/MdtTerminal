// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/DeviceHandle.h"
#include "Mdt/Usb/DeviceEnumerator.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("basicTest")
{
  auto context = std::make_shared<Context>();
  DeviceEnumerator deviceEnumerator(context);
  LibusbDeviceList deviceList = deviceEnumerator.scanForAttachedDevices();
  REQUIRE( deviceList.count() > 0 );

  /*
   * We try to open a random device.
   * Chances are, we don't have permissions.
   */
  try{
    auto handle = DeviceHandle::open( deviceList.libusbDevicePointerAt(0) );
  }catch(const LibusbRuntimeError &){
  }
}
