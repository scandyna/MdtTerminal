// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PinoutSignals.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("defaultConstructed")
{
  PinoutSignals ps;

  CHECK( !ps.receiveDataIsOn() );
}

TEST_CASE("set_TX")
{
  PinoutSignals ps;

  ps.setReceiveDataOn(true);
  CHECK( ps.receiveDataIsOn() );

  ps.setReceiveDataOn(false);
  CHECK( !ps.receiveDataIsOn() );
}

TEST_CASE("comparison")
{
  PinoutSignals a;
  PinoutSignals b;

  SECTION("default constructed a and b are equal")
  {
    CHECK( a == b );
    CHECK( !(a != b) );
  }

  SECTION("RX differs")
  {
    a.setReceiveDataOn(true);

    CHECK( a != b );
    CHECK( !(a == b) );
  }
}
