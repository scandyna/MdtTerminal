// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/LibusbError.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("errorFromInt")
{
  CHECK( LibusbError::errorFromInt(LIBUSB_ERROR_ACCESS) == LIBUSB_ERROR_ACCESS );
}

TEST_CASE("errorNameFromInt")
{
  CHECK( LibusbError::errorNameFromInt(LIBUSB_ERROR_NOT_SUPPORTED) == "LIBUSB_ERROR_NOT_SUPPORTED" );
}
