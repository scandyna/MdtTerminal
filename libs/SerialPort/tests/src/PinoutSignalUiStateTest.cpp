// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PinoutSignalUiState.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("initialState")
{
  PinoutSignalUiState s;

  REQUIRE( !s.stateHasChanged() );
  REQUIRE( !s.stateIsOn() );
}

TEST_CASE("PinoutSignalUiState")
{
  PinoutSignalUiState s;
  REQUIRE( !s.stateHasChanged() );
  REQUIRE( !s.stateIsOn() );

  SECTION("only 1 ON notified")
  {
    s.setSignalOn(true);

    s.updateState();

    REQUIRE( s.stateHasChanged() );
    CHECK( s.stateIsOn() );
  }

  SECTION("only 1 ON notified - 2 iterations")
  {
    s.setSignalOn(true);

    s.updateState();

    REQUIRE( s.stateHasChanged() );
    CHECK( s.stateIsOn() );

    s.setSignalOn(true);

    s.updateState();

    REQUIRE( !s.stateHasChanged() );
    CHECK( s.stateIsOn() );
  }

  SECTION("only 1 ON then in second iteration only 1 OFF")
  {
    s.setSignalOn(true);

    s.updateState();

    REQUIRE( s.stateHasChanged() );
    CHECK( s.stateIsOn() );

    s.setSignalOn(false);

    s.updateState();

    REQUIRE( s.stateHasChanged() );
    CHECK( !s.stateIsOn() );
  }
}
