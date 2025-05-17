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
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("fromLibusbDescriptor")
{
  libusb_device_descriptor libusbDescriptor;
  libusbDescriptor.idVendor = 0x1234;
  libusbDescriptor.idProduct = 0x5678;

  const auto descriptor = DeviceDescriptor::fromLibusbDescriptor(libusbDescriptor);

  CHECK( descriptor.libusbDescriptor().idVendor == 0x1234 );
  CHECK( descriptor.libusbDescriptor().idProduct == 0x5678 );
}
