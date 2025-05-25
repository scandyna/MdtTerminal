// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/EndpointDescriptor.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("fromLibusbDescriptor")
{
  libusb_endpoint_descriptor libusbEndoint;
  libusbEndoint.bEndpointAddress = 0x82;

  const auto endpoint = EndpointDescriptor::fromLibusbDescriptor(libusbEndoint);

  CHECK( endpoint.bEndpointAddress() == 0x82 );
}
