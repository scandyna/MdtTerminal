// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/InterfaceDescriptor.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("fromLibusbDescriptor")
{
  libusb_interface_descriptor libusbInterface;
  libusbInterface.bNumEndpoints = 1;

  const auto interface = InterfaceDescriptor::fromLibusbDescriptor(libusbInterface);

  CHECK( interface.bNumEndpoints() == 1 );
}
