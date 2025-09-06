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
using TimePoint = PinoutSignalUiStateTimer::TimePoint;
using namespace std::chrono_literals;


TEST_CASE("initialState")
{
  PinoutSignalUiState s;

  REQUIRE( !s.stateHasChanged() );
  REQUIRE( !s.stateIsOn() );
}

TEST_CASE("docTimeDiagramExample")
{
  PinoutSignalUiState s;

  s.setHoldOnDuration(100ms);
  s.setHoldOffDuration(40ms);

  s.setSignalOn( true, TimePoint(20ms) );
  CHECK( s.stateIsOn() );
  CHECK( s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(40ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setWatchdogTimeoutEvent( TimePoint(120ms) );
  CHECK( !s.stateIsOn() );
  CHECK( s.stateHasChanged() );

  s.setWatchdogTimeoutEvent( TimePoint(160ms) );
  CHECK( !s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( true, TimePoint(200ms) );
  CHECK( s.stateIsOn() );
  CHECK( s.stateHasChanged() );

  s.setSignalOn( true, TimePoint(220ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( true, TimePoint(240ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( true, TimePoint(260ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( true, TimePoint(280ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(300ms) );
  CHECK( !s.stateIsOn() );
  CHECK( s.stateHasChanged() );

  s.setWatchdogTimeoutEvent( TimePoint(340ms) );
  CHECK( !s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( true, TimePoint(400ms) );
  CHECK( s.stateIsOn() );
  CHECK( s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(420ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(440ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(460ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(480ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(500ms) );
  CHECK( !s.stateIsOn() );
  CHECK( s.stateHasChanged() );

  s.setWatchdogTimeoutEvent( TimePoint(540ms) );
  CHECK( !s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( true, TimePoint(600ms) );
  CHECK( s.stateIsOn() );
  CHECK( s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(620ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( true, TimePoint(640ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(660ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( true, TimePoint(680ms) );
  CHECK( s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(700ms) );
  CHECK( !s.stateIsOn() );
  CHECK( s.stateHasChanged() );

  s.setSignalOn( true, TimePoint(720ms) );
  CHECK( !s.stateIsOn() );
  CHECK( !s.stateHasChanged() );

  s.setSignalOn( false, TimePoint(740ms) );
  CHECK( !s.stateIsOn() );
  CHECK( !s.stateHasChanged() );
}

TEST_CASE("setStateOffNow")
{
  PinoutSignalUiState s;
  s.setHoldOnDuration(100ms);
  s.setHoldOffDuration(40ms);
  REQUIRE( !s.stateIsOn() );

  SECTION("when already OFF - no change")
  {
    s.setStateOffNow();

    CHECK( !s.stateIsOn() );
    CHECK( !s.stateHasChanged() );
  }

  SECTION("when currently ON - change to OFF")
  {
    s.setSignalOn( true, TimePoint(20ms) );
    REQUIRE( s.stateIsOn() );

    s.setStateOffNow();

    CHECK( !s.stateIsOn() );
    CHECK( s.stateHasChanged() );
  }
}
