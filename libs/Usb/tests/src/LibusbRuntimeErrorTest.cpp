// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/LibusbRuntimeError.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("errorCode")
{
  LibusbRuntimeError error("some I/O error", LIBUSB_ERROR_IO);

  CHECK( error.errorCode() == LIBUSB_ERROR_IO );
}
