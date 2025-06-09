// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/UsbVendorIdProductId.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("Comparison")
{
  UsbVendorIdProductId a;
  UsbVendorIdProductId b;

  SECTION("a and b VID 1")
  {
    a.vid = 1;
    b.vid = 1;

    a.pid = 0;
    b.pid = 0;
    CHECK( a == b );
    CHECK( !(a != b) );

    b.pid = 1;
    CHECK( !(a == b) );
    CHECK( a != b );
  }

  SECTION("a and b PID 25")
  {
    a.pid = 25;
    b.pid = 25;

    a.vid = 1;
    b.vid = 1;
    CHECK( a == b );
    CHECK( !(a != b) );

    a.vid = 25;
    CHECK( !(a == b) );
    CHECK( a != b );
  }
}
