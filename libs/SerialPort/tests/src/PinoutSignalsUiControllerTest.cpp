// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/TestLib/TestPinoutSignalsUiController.h"
#include "Mdt/SerialPort/TestLib/PinoutSignalUiStateChangedSignalSpy.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include <chrono>

using namespace Mdt::SerialPort;
using namespace std::chrono_literals;
using Mdt::SerialPort::TestLib::TestPinoutSignalsUiController;
using Mdt::SerialPort::TestLib::PinoutSignalUiStateChangedSignalSpy;
using TimePoint = TestPinoutSignalsUiController::TimePoint;


TEST_CASE("initialState")
{
  TestPinoutSignalsUiController psc;

  CHECK( !psc.watchdogTimerIsActive() );
}

TEST_CASE("watchdogTimerShouldBeActive")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);
  psc.setCurrentTime( TimePoint(20ms) );

  CHECK( !psc.watchdogTimerShouldBeActive() );

  SECTION("when RX UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setReceiveDataOn(true);
    psc.setSignals(ps);

    CHECK( psc.watchdogTimerShouldBeActive() );
  }

  SECTION("when TX UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setTransmitDataOn(true);
    psc.setSignals(ps);

    CHECK( psc.watchdogTimerShouldBeActive() );
  }

  SECTION("when DTR UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setDataTerminalReadyOn(true);
    psc.setSignals(ps);

    CHECK( psc.watchdogTimerShouldBeActive() );
  }

  SECTION("when RTS UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setRequestToSendOn(true);
    psc.setSignals(ps);

    CHECK( psc.watchdogTimerShouldBeActive() );
  }
}

TEST_CASE("whenAStateIsInHold_WdtIsActive_OtherwiseNot")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);

  CHECK( !psc.watchdogTimerIsActive() );

  psc.setCurrentTime( TimePoint(20ms) );
  ps.setReceiveDataOn(true);
  psc.setSignals(ps);

  CHECK( psc.watchdogTimerIsActive() );

  SECTION("after hold on timed out - RX ON notified - UiOn is no more a hold state")
  {
    psc.setCurrentTime( TimePoint(200ms) );
    ps.setReceiveDataOn(true);

    psc.setSignals(ps);

    CHECK( !psc.watchdogTimerIsActive() );
  }

  SECTION("after hold on timed out - on wathchdog timeout event - UiOn is no more a hold state")
  {
    psc.setCurrentTime( TimePoint(200ms) );

    psc.setWatchdogTimeoutEvent();

    CHECK( !psc.watchdogTimerIsActive() );
  }

  SECTION("on aboutToCloseEvent - even in hold state - wdt stops")
  {
    psc.setCurrentTime( TimePoint(25ms) );

    psc.setAboutToCloseEvent();

    CHECK( !psc.watchdogTimerIsActive() );
  }
}

TEST_CASE("whenPortIsAboutToClose_AllUiStatesGo_OFF")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);

  ps.setReceiveDataOn(true);
  ps.setTransmitDataOn(true);
  ps.setDataTerminalReadyOn(true);
  ps.setRequestToSendOn(true);
  psc.setSignals(ps);

  PinoutSignalUiStateChangedSignalSpy receiveDataChangedSpy(&psc, &TestPinoutSignalsUiController::receiveDataChanged);
  PinoutSignalUiStateChangedSignalSpy transmitDataChangedSpy(&psc, &TestPinoutSignalsUiController::transmitDataChanged);
  PinoutSignalUiStateChangedSignalSpy dataTerminalReadyChangedSpy(&psc, &TestPinoutSignalsUiController::dataTerminalReadyChanged);
  PinoutSignalUiStateChangedSignalSpy requestToSendChangedSpy(&psc, &TestPinoutSignalsUiController::requestToSendChanged);

  psc.setAboutToCloseEvent();

  REQUIRE( receiveDataChangedSpy.count() == 1 );
  CHECK( !receiveDataChangedSpy.stateAtIsOn(0) );

  REQUIRE( transmitDataChangedSpy.count() == 1 );
  CHECK( !transmitDataChangedSpy.stateAtIsOn(0) );

  REQUIRE( dataTerminalReadyChangedSpy.count() == 1 );
  CHECK( !dataTerminalReadyChangedSpy.stateAtIsOn(0) );

  REQUIRE( requestToSendChangedSpy.count() == 1 );
  CHECK( !requestToSendChangedSpy.stateAtIsOn(0) );
}

TEST_CASE("RX")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);
  PinoutSignalUiStateChangedSignalSpy receiveDataChangedSpy(&psc, &TestPinoutSignalsUiController::receiveDataChanged);

  SECTION("RX ON notified - UI goes ON")
  {
    ps.setReceiveDataOn(true);

    psc.setSignals(ps);

    REQUIRE( receiveDataChangedSpy.count() == 1 );
    CHECK( receiveDataChangedSpy.stateAtIsOn(0) );
  }

  SECTION("When RX UI is ON")
  {
    ps.setReceiveDataOn(true);
    psc.setSignals(ps);
    receiveDataChangedSpy.clear();

    SECTION("It stays ON on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( receiveDataChangedSpy.count() == 0 );
    }

    SECTION("when RX OFF is notified before hold on timed out - UI stays ON")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setReceiveDataOn(false);
      psc.setSignals(ps);

      REQUIRE( receiveDataChangedSpy.count() == 0 );
    }

    SECTION("When RX OFF is notified - RX UI goes OFF on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setReceiveDataOn(false);
      psc.setSignals(ps);
      REQUIRE( receiveDataChangedSpy.count() == 0 );

      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( receiveDataChangedSpy.count() == 1 );
      CHECK( !receiveDataChangedSpy.stateAtIsOn(0) );
    }
  }

  SECTION("When RX UI became OFF")
  {
    ps.setReceiveDataOn(true);
    psc.setSignals(ps);
    psc.setCurrentTime( TimePoint(200ms) );
    ps.setReceiveDataOn(false);
    psc.setSignals(ps);
    receiveDataChangedSpy.clear();

    ps.setReceiveDataOn(true);

    SECTION("when RX ON is notified before hold off timed out - RX UI stays OFF")
    {
      psc.setCurrentTime( TimePoint(220ms) );

      psc.setSignals(ps);

      REQUIRE( receiveDataChangedSpy.count() == 0 );
    }

    SECTION("when RX ON is notified after hold off timed out - RX UI goes ON")
    {
      psc.setCurrentTime( TimePoint(250ms) );

      psc.setSignals(ps);

      REQUIRE( receiveDataChangedSpy.count() == 1 );
      CHECK( receiveDataChangedSpy.stateAtIsOn(0) );
    }
  }

  /// \todo Wrong ! Must request OFF before
  // SECTION("UI is ON and goes OFF on wathchdog event after hold on timed out")
  // {
  //   ps.setReceiveDataOn(true);
  //   psc.setSignals(ps);
  //   receiveDataChangedSpy.clear();
  // 
  //   psc.setCurrentTime( TimePoint(150ms) );
  //   psc.setWatchdogTimeoutEvent();
  // 
  //   REQUIRE( receiveDataChangedSpy.count() == 1 );
  //   CHECK( !receiveDataChangedSpy.stateAtIsOn(0) );
  // }

  // SECTION("only 1 RX ON notified")
  // {
  //   ps.setReceiveDataOn(true);
  // 
  //   psc.setSignals(ps);
  // 
  //   psc.setTimerTimeoutEvent();
  // 
  //   REQUIRE( receiveDataChangedSpy.count() == 1 );
  //   CHECK( receiveDataChangedSpy.stateAtIsOn(0) );
  // }
}

TEST_CASE("TX")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);
  PinoutSignalUiStateChangedSignalSpy transmitDataChangedSpy(&psc, &TestPinoutSignalsUiController::transmitDataChanged);

  SECTION("TX ON notified - UI goes ON")
  {
    ps.setTransmitDataOn(true);

    psc.setSignals(ps);

    REQUIRE( transmitDataChangedSpy.count() == 1 );
    CHECK( transmitDataChangedSpy.stateAtIsOn(0) );
  }

  SECTION("When TX UI is ON")
  {
    ps.setTransmitDataOn(true);
    psc.setSignals(ps);
    transmitDataChangedSpy.clear();

    SECTION("It stays ON on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( transmitDataChangedSpy.count() == 0 );
    }

    SECTION("when TX OFF is notified before hold on timed out - UI stays ON")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setTransmitDataOn(false);
      psc.setSignals(ps);

      REQUIRE( transmitDataChangedSpy.count() == 0 );
    }

    SECTION("When TX OFF is notified - TX UI goes OFF on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setTransmitDataOn(false);
      psc.setSignals(ps);
      REQUIRE( transmitDataChangedSpy.count() == 0 );

      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( transmitDataChangedSpy.count() == 1 );
      CHECK( !transmitDataChangedSpy.stateAtIsOn(0) );
    }
  }

  SECTION("When TX UI became OFF")
  {
    ps.setTransmitDataOn(true);
    psc.setSignals(ps);
    psc.setCurrentTime( TimePoint(200ms) );
    ps.setTransmitDataOn(false);
    psc.setSignals(ps);
    transmitDataChangedSpy.clear();

    ps.setTransmitDataOn(true);

    SECTION("when TX ON is notified before hold off timed out - TX UI stays OFF")
    {
      psc.setCurrentTime( TimePoint(220ms) );

      psc.setSignals(ps);

      REQUIRE( transmitDataChangedSpy.count() == 0 );
    }

    SECTION("when TX ON is notified after hold off timed out - TX UI goes ON")
    {
      psc.setCurrentTime( TimePoint(250ms) );

      psc.setSignals(ps);

      REQUIRE( transmitDataChangedSpy.count() == 1 );
      CHECK( transmitDataChangedSpy.stateAtIsOn(0) );
    }
  }

  // SECTION("only 1 TX ON notified")
  // {
  //   ps.setTransmitDataOn(true);
  // 
  //   psc.setSignals(ps);
  // 
  //   psc.setWatchdogTimeoutEvent();
  // 
  //   REQUIRE( transmitDataChangedSpy.count() == 1 );
  //   CHECK( transmitDataChangedSpy.stateAtIsOn(0) );
  // }
}

TEST_CASE("DTR")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);
  PinoutSignalUiStateChangedSignalSpy dataTerminalReadyChangedSpy(&psc, &TestPinoutSignalsUiController::dataTerminalReadyChanged);

  SECTION("DTR ON notified - UI goes ON")
  {
    ps.setDataTerminalReadyOn(true);

    psc.setSignals(ps);

    REQUIRE( dataTerminalReadyChangedSpy.count() == 1 );
    CHECK( dataTerminalReadyChangedSpy.stateAtIsOn(0) );
  }

  SECTION("When DTR UI is ON")
  {
    ps.setDataTerminalReadyOn(true);
    psc.setSignals(ps);
    dataTerminalReadyChangedSpy.clear();

    SECTION("It stays ON on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( dataTerminalReadyChangedSpy.count() == 0 );
    }

    SECTION("when DTR OFF is notified before hold on timed out - UI stays ON")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setDataTerminalReadyOn(false);
      psc.setSignals(ps);

      REQUIRE( dataTerminalReadyChangedSpy.count() == 0 );
    }

    SECTION("When DTR OFF is notified - DTR UI goes OFF on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setDataTerminalReadyOn(false);
      psc.setSignals(ps);
      REQUIRE( dataTerminalReadyChangedSpy.count() == 0 );

      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( dataTerminalReadyChangedSpy.count() == 1 );
      CHECK( !dataTerminalReadyChangedSpy.stateAtIsOn(0) );
    }
  }

  SECTION("When DTR UI became OFF")
  {
    ps.setDataTerminalReadyOn(true);
    psc.setSignals(ps); // SM: --> on_hold
    psc.setCurrentTime( TimePoint(200ms) );
    ps.setDataTerminalReadyOn(false);
    psc.setSignals(ps); // SM: --> off_hold
    dataTerminalReadyChangedSpy.clear();

    ps.setDataTerminalReadyOn(true);

    SECTION("when DTR ON is notified before hold off timed out - DTR UI stays OFF")
    {
      psc.setCurrentTime( TimePoint(220ms) );

      psc.setSignals(ps);

      REQUIRE( dataTerminalReadyChangedSpy.count() == 0 );
    }

    SECTION("when DTR ON is notified after hold off timed out - DTR UI goes ON")
    {
      psc.setCurrentTime( TimePoint(250ms) );

      psc.setSignals(ps);

      REQUIRE( dataTerminalReadyChangedSpy.count() == 1 );
      CHECK( dataTerminalReadyChangedSpy.stateAtIsOn(0) );
    }
  }

  // SECTION("only 1 DTR ON notified")
  // {
  //   ps.setDataTerminalReadyOn(true);
  // 
  //   psc.setSignals(ps);
  // 
  //   psc.setWatchdogTimeoutEvent();
  // 
  //   REQUIRE( dataTerminalReadyChangedSpy.count() == 1 );
  //   CHECK( dataTerminalReadyChangedSpy.stateAtIsOn(0) );
  // }
}

TEST_CASE("RTS")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);
  PinoutSignalUiStateChangedSignalSpy requestToSendChangedSpy(&psc, &TestPinoutSignalsUiController::requestToSendChanged);

  SECTION("RTS ON notified - UI goes ON")
  {
    ps.setRequestToSendOn(true);

    psc.setSignals(ps);

    REQUIRE( requestToSendChangedSpy.count() == 1 );
    CHECK( requestToSendChangedSpy.stateAtIsOn(0) );
  }

  SECTION("When RTS UI is ON")
  {
    ps.setRequestToSendOn(true);
    psc.setSignals(ps);
    requestToSendChangedSpy.clear();

    SECTION("It stays ON on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( requestToSendChangedSpy.count() == 0 );
    }

    SECTION("when RTS OFF is notified before hold on timed out - UI stays ON")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setRequestToSendOn(false);
      psc.setSignals(ps);

      REQUIRE( requestToSendChangedSpy.count() == 0 );
    }

    SECTION("When RTS OFF is notified - RTS UI goes OFF on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setRequestToSendOn(false);
      psc.setSignals(ps);
      REQUIRE( requestToSendChangedSpy.count() == 0 );

      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( requestToSendChangedSpy.count() == 1 );
      CHECK( !requestToSendChangedSpy.stateAtIsOn(0) );
    }
  }

  SECTION("When RTS UI became OFF")
  {
    ps.setRequestToSendOn(true);
    psc.setSignals(ps); // SM: --> on_hold
    psc.setCurrentTime( TimePoint(200ms) );
    ps.setRequestToSendOn(false);
    psc.setSignals(ps); // SM: --> off_hold
    requestToSendChangedSpy.clear();

    ps.setRequestToSendOn(true);

    SECTION("when RTS ON is notified before hold off timed out - RTS UI stays OFF")
    {
      psc.setCurrentTime( TimePoint(220ms) );

      psc.setSignals(ps);

      REQUIRE( requestToSendChangedSpy.count() == 0 );
    }

    SECTION("when RTS ON is notified after hold off timed out - RTS UI goes ON")
    {
      psc.setCurrentTime( TimePoint(250ms) );

      psc.setSignals(ps);

      REQUIRE( requestToSendChangedSpy.count() == 1 );
      CHECK( requestToSendChangedSpy.stateAtIsOn(0) );
    }
  }
}
