// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PinoutSignalUiStateStateMachine.h"
#include "catch2/catch.hpp"

using namespace Mdt::SerialPort;
using State = PinoutSignalUiStateStateMachine::State;
using TimePoint = PinoutSignalUiStateTimer::TimePoint;
using namespace std::chrono_literals;


TEST_CASE("initialState")
{
  PinoutSignalUiStateStateMachine sm;

  CHECK( sm.currentState() == State::UiOff );
  CHECK( !sm.currentStateIs_off_hold() );
  CHECK( !sm.currentStateIs_on_hold() );
  CHECK( !sm.watchdogTimerShouldBeActive() );
  CHECK( !sm.uiOnOffStateHasChanged() );
  CHECK( !sm.uiStateIsOn() );
  CHECK( sm.holdOnTimerStartTime() == TimePoint(0ms) );
  CHECK( sm.holdOffTimerStartTime() == TimePoint(0ms) );
}

TEST_CASE("enter_on_hold_state")
{
  PinoutSignalUiStateStateMachine sm;
  const auto now = TimePoint(20ms);

  REQUIRE( sm.currentState() == State::UiOff );

  sm.enter_on_hold_state(now);

  CHECK( sm.currentState() == State::UiOnHold );
  CHECK( !sm.currentStateIs_off_hold() );
  CHECK( sm.currentStateIs_on_hold() );
  CHECK( sm.watchdogTimerShouldBeActive() );
  CHECK( sm.uiStateIsOn() );
  CHECK( sm.holdOnTimerStartTime() == TimePoint(20ms) );
  CHECK( sm.holdOffTimerStartTime() == TimePoint(0ms) );
}

TEST_CASE("enter_off_hold_state")
{
  PinoutSignalUiStateStateMachine sm;
  const auto now = TimePoint(20ms);

  REQUIRE( sm.currentState() == State::UiOff );

  sm.enter_off_hold_state(now);

  CHECK( sm.currentState() == State::UiOffHold );
  CHECK( sm.currentStateIs_off_hold() );
  CHECK( !sm.currentStateIs_on_hold() );
  CHECK( sm.watchdogTimerShouldBeActive() );
  CHECK( !sm.uiStateIsOn() );
  CHECK( sm.holdOnTimerStartTime() == TimePoint(0ms) );
  CHECK( sm.holdOffTimerStartTime() == TimePoint(20ms) );
}

TEST_CASE("UiOff")
{
  PinoutSignalUiStateStateMachine sm;
  REQUIRE( sm.currentState() == State::UiOff );

  CHECK( !sm.watchdogTimerShouldBeActive() );
  CHECK( !sm.uiOnOffStateHasChanged() );
  CHECK( !sm.uiStateIsOn() );

  SECTION("signal OFF does not change anything")
  {
    sm.setSignalOn( false, TimePoint(20ms) );

    CHECK( sm.currentState() == State::UiOff );
    CHECK( !sm.watchdogTimerShouldBeActive() );
    CHECK( !sm.uiOnOffStateHasChanged() );
    CHECK( !sm.uiStateIsOn() );
  }

  SECTION("signal ON - transition to UiOnHold")
  {
    sm.setSignalOn( true, TimePoint(20ms) );

    CHECK( sm.currentState() == State::UiOnHold );
    CHECK( sm.currentStateIs_on_hold() );
    CHECK( sm.watchdogTimerShouldBeActive() );
    CHECK( sm.uiOnOffStateHasChanged() );
    CHECK( sm.uiStateIsOn() );
  }

  SECTION("watchdog timeout does not change anything")
  {
    sm.setWatchdogTimeoutEvent( TimePoint(20ms) );

    CHECK( sm.currentState() == State::UiOff );
    CHECK( !sm.watchdogTimerShouldBeActive() );
    CHECK( !sm.uiOnOffStateHasChanged() );
    CHECK( !sm.uiStateIsOn() );
  }
}

TEST_CASE("on_hold")
{
  PinoutSignalUiStateStateMachine sm;
  sm.setHoldOnDuration(100ms);
  sm.setHoldOffDuration(40ms);
  sm.setSignalOn( true, TimePoint(20ms) );
  REQUIRE( sm.currentStateIs_on_hold() );

  SECTION("before hold on timed out")
  {
    const auto now = TimePoint(50ms);

    SECTION("UiOnHold")
    {
      REQUIRE( sm.currentState() == State::UiOnHold );
      CHECK( sm.currentStateIs_on_hold() );

      SECTION("signal ON - only reset UI state changed")
      {
        sm.setSignalOn(true, now);

        CHECK( sm.currentState() == State::UiOnHold );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }

      SECTION("signal OFF - transition to UiOnHoldOffRequested")
      {
        sm.setSignalOn(false, now);

        CHECK( sm.currentState() == State::UiOnHoldOffRequested );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }

      SECTION("watchdog timeout - only reset UI state changed")
      {
        sm.setWatchdogTimeoutEvent(now);

        CHECK( sm.currentState() == State::UiOnHold );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }
    }

    SECTION("UiOnHoldOffRequested")
    {
      sm.setSignalOn(false, now);
      REQUIRE( sm.currentState() == State::UiOnHoldOffRequested );
      CHECK( sm.currentStateIs_on_hold() );

      SECTION("signal ON - transition to UiOnHold")
      {
        sm.setSignalOn(true, now);

        CHECK( sm.currentState() == State::UiOnHold );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }

      SECTION("signal OFF - nothing changes")
      {
        sm.setSignalOn(false, now);

        CHECK( sm.currentState() == State::UiOnHoldOffRequested );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }

      SECTION("watchdog timeout - nothing changes")
      {
        sm.setWatchdogTimeoutEvent(now);

        CHECK( sm.currentState() == State::UiOnHoldOffRequested );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }
    }
  }

  SECTION("when hold on timed out")
  {
    const auto now = TimePoint(150ms);

    SECTION("UiOnHold")
    {
      REQUIRE( sm.currentState() == State::UiOnHold );
      CHECK( sm.currentStateIs_on_hold() );

      SECTION("signal ON - transition to UiOn")
      {
        sm.setSignalOn(true, now);

        CHECK( sm.currentState() == State::UiOn );
        CHECK( !sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }

      SECTION("signal OFF - transition to off_hold")
      {
        sm.setSignalOn(false, now);

        CHECK( sm.currentStateIs_off_hold() );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }

      SECTION("watchdog timeout - transition to UiOn")
      {
        sm.setWatchdogTimeoutEvent(now);

        CHECK( sm.currentState() == State::UiOn );
        CHECK( !sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }
    }

    SECTION("UiOnHoldOffRequested")
    {
      sm.setSignalOn( false, TimePoint(50ms) );
      REQUIRE( sm.currentState() == State::UiOnHoldOffRequested );
      CHECK( sm.currentStateIs_on_hold() );

      SECTION("signal ON - transition to UiOn")
      {
        sm.setSignalOn(true, now);

        CHECK( sm.currentState() == State::UiOn );
        CHECK( !sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }

      SECTION("signal OFF - transition to off_hold")
      {
        sm.setSignalOn(false, now);

        CHECK( sm.currentStateIs_off_hold() );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }

      SECTION("watchdog timeout - transition to off_hold")
      {
        sm.setWatchdogTimeoutEvent(now);

        CHECK( sm.currentStateIs_off_hold() );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }
    }
  }
}

TEST_CASE("UiOnHold")
{
  PinoutSignalUiStateStateMachine sm;
  sm.setHoldOnDuration(100ms);
  sm.setHoldOffDuration(40ms);
  sm.setSignalOn( true, TimePoint(20ms) );
  REQUIRE( sm.currentState() == State::UiOnHold );

  CHECK( sm.watchdogTimerShouldBeActive() );
  CHECK( sm.uiOnOffStateHasChanged() );
  CHECK( sm.uiStateIsOn() );

  SECTION("signal ON before hold on timeout - only reset UI state changed")
  {
    sm.setSignalOn( true, TimePoint(20ms) );

    CHECK( sm.currentState() == State::UiOnHold );
    CHECK( sm.watchdogTimerShouldBeActive() );
    CHECK( !sm.uiOnOffStateHasChanged() );
    CHECK( sm.uiStateIsOn() );
  }

  SECTION("signal OFF before hold on timeout - transition to UiOnHoldOffRequested")
  {
    sm.setSignalOn( false, TimePoint(20ms) );

    CHECK( sm.currentState() == State::UiOnHoldOffRequested );
    CHECK( sm.watchdogTimerShouldBeActive() );
    CHECK( !sm.uiOnOffStateHasChanged() );
    CHECK( sm.uiStateIsOn() );
  }

  SECTION("signal ON when hold on timed out - transition to UiOn")
  {
    sm.setSignalOn( true, TimePoint(120ms) );

    CHECK( sm.currentState() == State::UiOn );
    CHECK( !sm.watchdogTimerShouldBeActive() );
    CHECK( !sm.uiOnOffStateHasChanged() );
    CHECK( sm.uiStateIsOn() );
  }

  SECTION("signal OFF when hold on timed out - transition to UiOffHold")
  {
    sm.setSignalOn( false, TimePoint(120ms) );

    CHECK( sm.currentState() == State::UiOffHold );
    CHECK( sm.watchdogTimerShouldBeActive() );
    CHECK( sm.uiOnOffStateHasChanged() );
    CHECK( !sm.uiStateIsOn() );
  }

  SECTION("watchdog timeout before hold on timeout - only reset UI state changed")
  {
    sm.setWatchdogTimeoutEvent( TimePoint(20ms) );

    CHECK( sm.currentState() == State::UiOnHold );
    CHECK( sm.watchdogTimerShouldBeActive() );
    CHECK( !sm.uiOnOffStateHasChanged() );
    CHECK( sm.uiStateIsOn() );
  }

  SECTION("watchdog timeout when hold on timed out - transition to UiOn")
  {
    sm.setWatchdogTimeoutEvent( TimePoint(120ms) );

    CHECK( sm.currentState() == State::UiOn );
    CHECK( !sm.watchdogTimerShouldBeActive() );
    CHECK( !sm.uiOnOffStateHasChanged() );
    CHECK( sm.uiStateIsOn() );
  }
}

TEST_CASE("UiOnHoldOffRequested")
{
  PinoutSignalUiStateStateMachine sm;
  sm.setHoldOnDuration(100ms);
  sm.setHoldOffDuration(40ms);
  sm.setSignalOn( true, TimePoint(20ms) );
  sm.setSignalOn( false, TimePoint(40ms) );
  REQUIRE( sm.currentState() == State::UiOnHoldOffRequested );

  CHECK( sm.watchdogTimerShouldBeActive() );
  CHECK( !sm.uiOnOffStateHasChanged() );
  CHECK( sm.uiStateIsOn() );

  SECTION("before hold on timed out")
  {
    const auto now = TimePoint(50ms);

    SECTION("signal ON - transition to UiOnHold")
    {
      sm.setSignalOn(true, now);

      CHECK( sm.currentState() == State::UiOnHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( sm.uiStateIsOn() );
    }

    SECTION("signal OFF - nothing changes")
    {
      sm.setSignalOn(false, now);

      CHECK( sm.currentState() == State::UiOnHoldOffRequested );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( sm.uiStateIsOn() );
    }

    SECTION("watchdog timeout - nothing changes")
    {
      sm.setWatchdogTimeoutEvent(now);

      CHECK( sm.currentState() == State::UiOnHoldOffRequested );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( sm.uiStateIsOn() );
    }
  }

  SECTION("when hold on timed out")
  {
    const auto now = TimePoint(150ms);

    // SECTION("signal (ON) - transition to UiOffHold")
    // {
    //   sm.setSignalOn(true, now);
    // 
    //   CHECK( sm.currentState() == State::UiOffHold );
    //   CHECK( sm.watchdogTimerShouldBeActive() );
    //   CHECK( sm.uiOnOffStateHasChanged() );
    //   CHECK( !sm.uiStateIsOn() );
    // }

    SECTION("signal (OFF) - transition to UiOffHold")
    {
      sm.setSignalOn(false, now);

      CHECK( sm.currentState() == State::UiOffHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }

    SECTION("watchdog timeout - transition to UiOffHold")
    {
      sm.setWatchdogTimeoutEvent(now);

      CHECK( sm.currentState() == State::UiOffHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }
  }
}

TEST_CASE("UiOn")
{
  PinoutSignalUiStateStateMachine sm;
  sm.setHoldOnDuration(100ms);
  sm.setHoldOffDuration(40ms);
  sm.setSignalOn( true, TimePoint(20ms) );
  sm.setSignalOn( true, TimePoint(200ms) );
  REQUIRE( sm.currentState() == State::UiOn );

  CHECK( !sm.watchdogTimerShouldBeActive() );
  CHECK( !sm.uiOnOffStateHasChanged() );
  CHECK( sm.uiStateIsOn() );

  SECTION("before hold off timed out")
  {
    const auto now = TimePoint(50ms);

    SECTION("signal ON - nothing changes")
    {
      sm.setSignalOn(true, now);

      CHECK( sm.currentState() == State::UiOn );
      CHECK( !sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( sm.uiStateIsOn() );
    }

    SECTION("signal OFF - transition to UiOffHold")
    {
      sm.setSignalOn(false, now);

      CHECK( sm.currentState() == State::UiOffHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }

    SECTION("watchdog timeout - nothing changes")
    {
      sm.setWatchdogTimeoutEvent(now);

      CHECK( sm.currentState() == State::UiOn );
      CHECK( !sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( sm.uiStateIsOn() );
    }
  }

  SECTION("when hold off timed out (the same as before timeout - should not care on timer)")
  {
    const auto now = TimePoint(250ms);

    SECTION("signal ON - nothing changes")
    {
      sm.setSignalOn(true, now);

      CHECK( sm.currentState() == State::UiOn );
      CHECK( !sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( sm.uiStateIsOn() );
    }

    SECTION("signal OFF - transition to UiOffHold")
    {
      sm.setSignalOn(false, now);

      CHECK( sm.currentState() == State::UiOffHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }

    SECTION("watchdog timeout - nothing changes")
    {
      sm.setWatchdogTimeoutEvent(now);

      CHECK( sm.currentState() == State::UiOn );
      CHECK( !sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( sm.uiStateIsOn() );
    }
  }
}

TEST_CASE("off_hold")
{
  PinoutSignalUiStateStateMachine sm;
  sm.setHoldOnDuration(100ms);
  sm.setHoldOffDuration(40ms);
  sm.setSignalOn( true, TimePoint(20ms) );    // -> on_hold
  sm.setSignalOn( false, TimePoint(200ms) );  // -> off_hold
  REQUIRE( sm.currentStateIs_off_hold() );

  SECTION("before hold off timed out")
  {
    const auto now = TimePoint(50ms);

    SECTION("UiOffHold")
    {
      REQUIRE( sm.currentState() == State::UiOffHold );
      CHECK( sm.currentStateIs_off_hold() );

      SECTION("signal ON - transition to UiOffHoldOnRequested")
      {
        sm.setSignalOn(true, now);

        CHECK( sm.currentState() == State::UiOffHoldOnRequested );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }

      SECTION("signal OFF - only reset UI state changed")
      {
        sm.setSignalOn(false, now);

        CHECK( sm.currentState() == State::UiOffHold );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }

      SECTION("watchdog timeout - only reset UI state changed")
      {
        sm.setWatchdogTimeoutEvent(now);

        CHECK( sm.currentState() == State::UiOffHold );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }
    }

    SECTION("UiOffHoldOnRequested")
    {
      sm.setSignalOn(true, now);
      REQUIRE( sm.currentState() == State::UiOffHoldOnRequested );
      CHECK( sm.currentStateIs_off_hold() );

      SECTION("signal ON - nothing changes")
      {
        sm.setSignalOn(true, now);

        CHECK( sm.currentState() == State::UiOffHoldOnRequested );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }

      SECTION("signal OFF - transition to UiOffHold")
      {
        sm.setSignalOn(false, now);

        CHECK( sm.currentState() == State::UiOffHold );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }

      SECTION("watchdog timeout - nothing changes")
      {
        sm.setWatchdogTimeoutEvent(now);

        CHECK( sm.currentState() == State::UiOffHoldOnRequested );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }
    }
  }

  SECTION("when hold off timed out")
  {
    const auto now = TimePoint(300ms);

    SECTION("UiOffHold")
    {
      REQUIRE( sm.currentState() == State::UiOffHold );
      CHECK( sm.currentStateIs_off_hold() );

      SECTION("signal ON - transition to on_hold")
      {
        sm.setSignalOn(true, now);

        CHECK( sm.currentStateIs_on_hold() );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }

      SECTION("signal OFF - transition to UiOff")
      {
        sm.setSignalOn(false, now);

        CHECK( sm.currentState() == State::UiOff );
        CHECK( !sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }

      SECTION("watchdog timeout - transition to UiOff")
      {
        sm.setWatchdogTimeoutEvent(now);

        CHECK( sm.currentState() == State::UiOff );
        CHECK( !sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }
    }

    SECTION("UiOffHoldOnRequested")
    {
      sm.setSignalOn( true, TimePoint(50ms) );
      REQUIRE( sm.currentState() == State::UiOffHoldOnRequested );
      CHECK( sm.currentStateIs_off_hold() );

      SECTION("signal ON - transition to on_hold")
      {
        sm.setSignalOn(true, now);

        CHECK( sm.currentStateIs_on_hold() );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }

      SECTION("signal OFF - transition to UiOff")
      {
        sm.setSignalOn(false, now);

        CHECK( sm.currentState() == State::UiOff );
        CHECK( !sm.watchdogTimerShouldBeActive() );
        CHECK( !sm.uiOnOffStateHasChanged() );
        CHECK( !sm.uiStateIsOn() );
      }

      SECTION("watchdog timeout - transition to on_hold")
      {
        sm.setWatchdogTimeoutEvent(now);

        CHECK( sm.currentStateIs_on_hold() );
        CHECK( sm.watchdogTimerShouldBeActive() );
        CHECK( sm.uiOnOffStateHasChanged() );
        CHECK( sm.uiStateIsOn() );
      }
    }
  }
}

TEST_CASE("UiOffHold")
{
  PinoutSignalUiStateStateMachine sm;
  sm.setHoldOnDuration(100ms);
  sm.setHoldOffDuration(40ms);
  sm.setSignalOn( true, TimePoint(20ms) );    // -> UiOnHold
  sm.setSignalOn( false, TimePoint(40ms) );   // -> UiOnHoldOffRequested
  sm.setSignalOn( false, TimePoint(200ms) );  // -> UiOffHold
  REQUIRE( sm.currentState() == State::UiOffHold );

  CHECK( sm.watchdogTimerShouldBeActive() );
  CHECK( sm.uiOnOffStateHasChanged() );
  CHECK( !sm.uiStateIsOn() );

  SECTION("before hold off timed out")
  {
    const auto now = TimePoint(50ms);

    SECTION("signal ON - transition to UiOffHoldOnRequested")
    {
      sm.setSignalOn(true, now);

      CHECK( sm.currentState() == State::UiOffHoldOnRequested );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }

    SECTION("signal OFF - only reset UI state changed")
    {
      sm.setSignalOn(false, now);

      CHECK( sm.currentState() == State::UiOffHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }

    SECTION("watchdog timeout - only reset UI state changed")
    {
      sm.setWatchdogTimeoutEvent(now);

      CHECK( sm.currentState() == State::UiOffHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }
  }

  SECTION("when hold off timed out")
  {
    const auto now = TimePoint(250ms);

    SECTION("signal ON - transition to UiOnHold")
    {
      sm.setSignalOn(true, now);

      CHECK( sm.currentState() == State::UiOnHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( sm.uiOnOffStateHasChanged() );
      CHECK( sm.uiStateIsOn() );
    }

    SECTION("signal OFF - transition to UiOff")
    {
      sm.setSignalOn(false, now);

      CHECK( sm.currentState() == State::UiOff );
      CHECK( !sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }

    SECTION("watchdog timeout - transition to UiOff")
    {
      sm.setWatchdogTimeoutEvent(now);

      CHECK( sm.currentState() == State::UiOff );
      CHECK( !sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }
  }
}

TEST_CASE("UiOffHoldOnRequested")
{
  PinoutSignalUiStateStateMachine sm;
  sm.setHoldOnDuration(100ms);
  sm.setHoldOffDuration(40ms);
  sm.setSignalOn( true, TimePoint(20ms) );    // -> UiOnHold
  sm.setSignalOn( true, TimePoint(200ms) );   // -> UiOn
  sm.setSignalOn( false, TimePoint(210ms) );  // -> UiOffHold (resets hold off timer)
  sm.setSignalOn( true, TimePoint(220ms) );   // -> UiOffHoldOnRequested
  REQUIRE( sm.currentState() == State::UiOffHoldOnRequested );

  CHECK( sm.watchdogTimerShouldBeActive() );
  CHECK( !sm.uiOnOffStateHasChanged() );
  CHECK( !sm.uiStateIsOn() );

  SECTION("before hold off timed out")
  {
    const auto now = TimePoint(230ms);

    SECTION("signal ON - nothing changes")
    {
      sm.setSignalOn(true, now);

      CHECK( sm.currentState() == State::UiOffHoldOnRequested );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }

    SECTION("signal OFF - transition to UiOffHold")
    {
      sm.setSignalOn(false, now);

      CHECK( sm.currentState() == State::UiOffHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }

    SECTION("watchdog timeout - nothing changes")
    {
      sm.setWatchdogTimeoutEvent(now);

      CHECK( sm.currentState() == State::UiOffHoldOnRequested );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( !sm.uiOnOffStateHasChanged() );
      CHECK( !sm.uiStateIsOn() );
    }
  }

  SECTION("when hold off timed out")
  {
    const auto now = TimePoint(400ms);

    SECTION("signal (ON) - transition to UiOnHold")
    {
      sm.setSignalOn(true, now);

      CHECK( sm.currentState() == State::UiOnHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( sm.uiOnOffStateHasChanged() );
      CHECK( sm.uiStateIsOn() );
    }

    // SECTION("signal (OFF) - transition to UiOnHold")
    // {
    //   sm.setSignalOn(false, now);
    // 
    //   CHECK( sm.currentState() == State::UiOnHold );
    //   CHECK( sm.watchdogTimerShouldBeActive() );
    //   CHECK( sm.uiOnOffStateHasChanged() );
    //   CHECK( sm.uiStateIsOn() );
    // }

    SECTION("watchdog timeout - transition to UiOnHold")
    {
      sm.setWatchdogTimeoutEvent(now);

      CHECK( sm.currentState() == State::UiOnHold );
      CHECK( sm.watchdogTimerShouldBeActive() );
      CHECK( sm.uiOnOffStateHasChanged() );
      CHECK( sm.uiStateIsOn() );
    }
  }
}

// TEST_CASE("transitionFrom_UiOn_to_UiOffHold_startsHoldOffTimer")
// {
//   PinoutSignalUiStateStateMachine sm;
//   sm.setHoldOnDuration(100ms);
//   sm.setHoldOffDuration(40ms);
//   sm.setSignalOn( true, TimePoint(20ms) );
//   sm.setSignalOn( true, TimePoint(200ms) );
//   REQUIRE( sm.currentState() == State::UiOn );
// 
//   // Should start hold off timer
//   const auto now = TimePoint(500ms);
//   sm.setSignalOn( false, now );
//   CHECK( sm.currentState() == State::UiOffHold );
// 
//   // Before timeout - signal OFF should not change state
//   sm.setSignalOn( false, now + 20ms );
//   CHECK( sm.currentState() == State::UiOffHold );
// 
//   // After timeout - transition to UiOff
//   sm.setSignalOn( false, now + 50ms );
//   CHECK( sm.currentState() == State::UiOff );
// }
// 
// TEST_CASE("transitionFrom_UiOnHold_to_UiOffHold_startsHoldOffTimer")
// {
//   PinoutSignalUiStateStateMachine sm;
//   sm.setHoldOnDuration(100ms);
//   sm.setHoldOffDuration(40ms);
//   sm.setSignalOn( true, TimePoint(20ms) );    // -> UiOnHold
//   REQUIRE( sm.currentState() == State::UiOnHold );
// 
//   // Should start hold off timer
//   const auto now = TimePoint(500ms);
//   sm.setSignalOn( false, now );
//   CHECK( sm.currentState() == State::UiOffHold );
// 
//   // Before timeout - signal OFF should not change state
//   sm.setSignalOn( false, now + 20ms );
//   CHECK( sm.currentState() == State::UiOffHold );
// 
//   // After timeout - transition to UiOff
//   sm.setSignalOn( false, now + 50ms );
//   CHECK( sm.currentState() == State::UiOff );
// }
// 
// TEST_CASE("transitionFrom_UiOnHoldOffRequested_to_UiOffHold_startsHoldOffTimer")
// {
//   PinoutSignalUiStateStateMachine sm;
//   sm.setHoldOnDuration(100ms);
//   sm.setHoldOffDuration(40ms);
//   sm.setSignalOn( true, TimePoint(20ms) );
//   sm.setSignalOn( false, TimePoint(40ms) );
//   REQUIRE( sm.currentState() == State::UiOnHoldOffRequested );
// 
//   // Should start hold off timer
//   const auto now = TimePoint(500ms);
//   sm.setSignalOn( false, now );
//   CHECK( sm.currentState() == State::UiOffHold );
// 
//   // Before timeout - signal OFF should not change state
//   sm.setSignalOn( false, now + 20ms );
//   CHECK( sm.currentState() == State::UiOffHold );
// 
//   // After timeout - transition to UiOff
//   sm.setSignalOn( false, now + 50ms );
//   CHECK( sm.currentState() == State::UiOff );
// }

// TEST_CASE("transitionFrom_UiOff_to_UiOnHold_startsHoldOnTimer")
// {
//   PinoutSignalUiStateStateMachine sm;
//   sm.setHoldOnDuration(100ms);
//   sm.setHoldOffDuration(40ms);
//   REQUIRE( sm.currentState() == State::UiOff );
// 
//   // Should start hold on timer
//   const auto now = TimePoint(500ms);
//   sm.setSignalOn( true, now );
//   CHECK( sm.currentState() == State::UiOnHold );
// 
//   // Before timeout - signal ON should not change state
//   sm.setSignalOn( true, now + 20ms );
//   CHECK( sm.currentState() == State::UiOnHold );
// 
//   // After timeout - transition to UiOn
//   sm.setSignalOn( true, now + 150ms );
//   CHECK( sm.currentState() == State::UiOn );
// }

// TEST_CASE("transitionFrom_UiOffHoldOnRequested_to_UiOnHold_startsHoldOnTimer")
// {
//   PinoutSignalUiStateStateMachine sm;
//   sm.setHoldOnDuration(100ms);
//   sm.setHoldOffDuration(40ms);
//   sm.setSignalOn( true, TimePoint(20ms) );    // -> UiOnHold
//   sm.setSignalOn( false, TimePoint(30ms) );   // -> UiOnHoldOffRequested
//   sm.setSignalOn( false, TimePoint(200ms) );  // -> UiOffHold
//   sm.setSignalOn( true, TimePoint(210ms) );   // -> UiOffHoldOnRequested
//   REQUIRE( sm.currentState() == State::UiOffHoldOnRequested );
// 
//   // Should start hold on timer
//   const auto now = TimePoint(500ms);
//   sm.setSignalOn( true, now );
//   CHECK( sm.currentState() == State::UiOnHold );
// 
//   // Before timeout - signal ON should not change state
//   sm.setSignalOn( true, now + 20ms );
//   CHECK( sm.currentState() == State::UiOnHold );
// 
//   // After timeout - transition to UiOn
//   sm.setSignalOn( true, now + 150ms );
//   CHECK( sm.currentState() == State::UiOn );
// }

// TEST_CASE("transitionFrom_UiOffHold_to_UiOnHold_startsHoldOnTimer")
// {
//   PinoutSignalUiStateStateMachine sm;
//   sm.setHoldOnDuration(100ms);
//   sm.setHoldOffDuration(40ms);
//   sm.setSignalOn( true, TimePoint(20ms) );    // -> UiOnHold
//   sm.setSignalOn( false, TimePoint(30ms) );   // -> UiOnHoldOffRequested
//   sm.setSignalOn( false, TimePoint(200ms) );  // -> UiOffHold
//   REQUIRE( sm.currentState() == State::UiOffHold );
// 
//   // Should start hold on timer
//   const auto now = TimePoint(500ms);
//   sm.setSignalOn( true, now );
//   CHECK( sm.currentState() == State::UiOnHold );
// 
//   // Before timeout - signal ON should not change state
//   sm.setSignalOn( true, now + 20ms );
//   CHECK( sm.currentState() == State::UiOnHold );
// 
//   // After timeout - transition to UiOn
//   sm.setSignalOn( true, now + 150ms );
//   CHECK( sm.currentState() == State::UiOn );
// }
