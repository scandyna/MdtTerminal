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

  SECTION("when RTS UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setRequestToSendOn(true);
    psc.setSignals(ps);

    CHECK( psc.watchdogTimerShouldBeActive() );
  }

  SECTION("when CTS UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setClearToSendOn(true);
    psc.setSignals(ps);

    CHECK( psc.watchdogTimerShouldBeActive() );
  }

  SECTION("when DCD UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setDataCarrierDetectOn(true);
    psc.setSignals(ps);

    CHECK( psc.watchdogTimerShouldBeActive() );
  }

  SECTION("when DSR UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setDataSetReadyOn(true);
    psc.setSignals(ps);

    CHECK( psc.watchdogTimerShouldBeActive() );
  }

  SECTION("when DTR UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setDataTerminalReadyOn(true);
    psc.setSignals(ps);

    CHECK( psc.watchdogTimerShouldBeActive() );
  }

  SECTION("when RNG UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setRingIndicatorOn(true);
    psc.setSignals(ps);

    CHECK( psc.watchdogTimerShouldBeActive() );
  }

  SECTION("when break UI goes ON (hold state) - wdt shoud be active")
  {
    ps.setBreakOn(true);
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
  ps.setRequestToSendOn(true);
  ps.setClearToSendOn(true);
  ps.setDataCarrierDetectOn(true);
  ps.setDataSetReadyOn(true);
  ps.setDataTerminalReadyOn(true);
  ps.setRingIndicatorOn(true);
  ps.setBreakOn(true);
  psc.setSignals(ps);

  PinoutSignalUiStateChangedSignalSpy receiveDataChangedSpy(&psc, &TestPinoutSignalsUiController::receiveDataChanged);
  PinoutSignalUiStateChangedSignalSpy transmitDataChangedSpy(&psc, &TestPinoutSignalsUiController::transmitDataChanged);

  PinoutSignalUiStateChangedSignalSpy requestToSendChangedSpy(&psc, &TestPinoutSignalsUiController::requestToSendChanged);
  PinoutSignalUiStateChangedSignalSpy clearToSendChangedSpy(&psc, &TestPinoutSignalsUiController::clearToSendChanged);
  PinoutSignalUiStateChangedSignalSpy dataCarrierDetectChangedSpy(&psc, &TestPinoutSignalsUiController::dataCarrierDetectChanged);
  PinoutSignalUiStateChangedSignalSpy dataSetReadyChangedSpy(&psc, &TestPinoutSignalsUiController::dataSetReadyChanged);
  PinoutSignalUiStateChangedSignalSpy dataTerminalReadyChangedSpy(&psc, &TestPinoutSignalsUiController::dataTerminalReadyChanged);
  PinoutSignalUiStateChangedSignalSpy ringIndicatorChangedSpy(&psc, &TestPinoutSignalsUiController::ringIndicatorChanged);

  PinoutSignalUiStateChangedSignalSpy breakChangedSpy(&psc, &TestPinoutSignalsUiController::breakChanged);

  psc.setAboutToCloseEvent();

  REQUIRE( receiveDataChangedSpy.count() == 1 );
  CHECK( !receiveDataChangedSpy.stateAtIsOn(0) );

  REQUIRE( transmitDataChangedSpy.count() == 1 );
  CHECK( !transmitDataChangedSpy.stateAtIsOn(0) );

  REQUIRE( requestToSendChangedSpy.count() == 1 );
  CHECK( !requestToSendChangedSpy.stateAtIsOn(0) );

  REQUIRE( clearToSendChangedSpy.count() == 1 );
  CHECK( !clearToSendChangedSpy.stateAtIsOn(0) );

  REQUIRE( dataCarrierDetectChangedSpy.count() == 1 );
  CHECK( !dataCarrierDetectChangedSpy.stateAtIsOn(0) );

  REQUIRE( dataSetReadyChangedSpy.count() == 1 );
  CHECK( !dataSetReadyChangedSpy.stateAtIsOn(0) );

  REQUIRE( dataTerminalReadyChangedSpy.count() == 1 );
  CHECK( !dataTerminalReadyChangedSpy.stateAtIsOn(0) );

  REQUIRE( ringIndicatorChangedSpy.count() == 1 );
  CHECK( !ringIndicatorChangedSpy.stateAtIsOn(0) );

  REQUIRE( breakChangedSpy.count() == 1 );
  CHECK( !breakChangedSpy.stateAtIsOn(0) );
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

TEST_CASE("CTS")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);
  PinoutSignalUiStateChangedSignalSpy clearToSendChangedSpy(&psc, &TestPinoutSignalsUiController::clearToSendChanged);

  SECTION("CTS ON notified - UI goes ON")
  {
    ps.setClearToSendOn(true);

    psc.setSignals(ps);

    REQUIRE( clearToSendChangedSpy.count() == 1 );
    CHECK( clearToSendChangedSpy.stateAtIsOn(0) );
  }

  SECTION("When CTS UI is ON")
  {
    ps.setClearToSendOn(true);
    psc.setSignals(ps);
    clearToSendChangedSpy.clear();

    SECTION("It stays ON on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( clearToSendChangedSpy.count() == 0 );
    }

    SECTION("when CTS OFF is notified before hold on timed out - UI stays ON")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setClearToSendOn(false);
      psc.setSignals(ps);

      REQUIRE( clearToSendChangedSpy.count() == 0 );
    }

    SECTION("When CTS OFF is notified - CTS UI goes OFF on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setClearToSendOn(false);
      psc.setSignals(ps);
      REQUIRE( clearToSendChangedSpy.count() == 0 );

      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( clearToSendChangedSpy.count() == 1 );
      CHECK( !clearToSendChangedSpy.stateAtIsOn(0) );
    }
  }

  SECTION("When CTS UI became OFF")
  {
    ps.setClearToSendOn(true);
    psc.setSignals(ps); // SM: --> on_hold
    psc.setCurrentTime( TimePoint(200ms) );
    ps.setClearToSendOn(false);
    psc.setSignals(ps); // SM: --> off_hold
    clearToSendChangedSpy.clear();

    ps.setClearToSendOn(true);

    SECTION("when CTS ON is notified before hold off timed out - CTS UI stays OFF")
    {
      psc.setCurrentTime( TimePoint(220ms) );

      psc.setSignals(ps);

      REQUIRE( clearToSendChangedSpy.count() == 0 );
    }

    SECTION("when CTS ON is notified after hold off timed out - CTS UI goes ON")
    {
      psc.setCurrentTime( TimePoint(250ms) );

      psc.setSignals(ps);

      REQUIRE( clearToSendChangedSpy.count() == 1 );
      CHECK( clearToSendChangedSpy.stateAtIsOn(0) );
    }
  }
}

TEST_CASE("DCD")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);
  PinoutSignalUiStateChangedSignalSpy dataCarrierDetectChangedSpy(&psc, &TestPinoutSignalsUiController::dataCarrierDetectChanged);

  SECTION("DCD ON notified - UI goes ON")
  {
    ps.setDataCarrierDetectOn(true);

    psc.setSignals(ps);

    REQUIRE( dataCarrierDetectChangedSpy.count() == 1 );
    CHECK( dataCarrierDetectChangedSpy.stateAtIsOn(0) );
  }

  SECTION("When DCD UI is ON")
  {
    ps.setDataCarrierDetectOn(true);
    psc.setSignals(ps);
    dataCarrierDetectChangedSpy.clear();

    SECTION("It stays ON on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( dataCarrierDetectChangedSpy.count() == 0 );
    }

    SECTION("when DCD OFF is notified before hold on timed out - UI stays ON")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setDataCarrierDetectOn(false);
      psc.setSignals(ps);

      REQUIRE( dataCarrierDetectChangedSpy.count() == 0 );
    }

    SECTION("When DCD OFF is notified - DCD UI goes OFF on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setDataCarrierDetectOn(false);
      psc.setSignals(ps);
      REQUIRE( dataCarrierDetectChangedSpy.count() == 0 );

      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( dataCarrierDetectChangedSpy.count() == 1 );
      CHECK( !dataCarrierDetectChangedSpy.stateAtIsOn(0) );
    }
  }

  SECTION("When DCD UI became OFF")
  {
    ps.setDataCarrierDetectOn(true);
    psc.setSignals(ps); // SM: --> on_hold
    psc.setCurrentTime( TimePoint(200ms) );
    ps.setDataCarrierDetectOn(false);
    psc.setSignals(ps); // SM: --> off_hold
    dataCarrierDetectChangedSpy.clear();

    ps.setDataCarrierDetectOn(true);

    SECTION("when DCD ON is notified before hold off timed out - DCD UI stays OFF")
    {
      psc.setCurrentTime( TimePoint(220ms) );

      psc.setSignals(ps);

      REQUIRE( dataCarrierDetectChangedSpy.count() == 0 );
    }

    SECTION("when DCD ON is notified after hold off timed out - DCD UI goes ON")
    {
      psc.setCurrentTime( TimePoint(250ms) );

      psc.setSignals(ps);

      REQUIRE( dataCarrierDetectChangedSpy.count() == 1 );
      CHECK( dataCarrierDetectChangedSpy.stateAtIsOn(0) );
    }
  }
}

TEST_CASE("DSR")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);
  PinoutSignalUiStateChangedSignalSpy dataSetReadyChangedSpy(&psc, &TestPinoutSignalsUiController::dataSetReadyChanged);

  SECTION("DSR ON notified - UI goes ON")
  {
    ps.setDataSetReadyOn(true);

    psc.setSignals(ps);

    REQUIRE( dataSetReadyChangedSpy.count() == 1 );
    CHECK( dataSetReadyChangedSpy.stateAtIsOn(0) );
  }

  SECTION("When DSR UI is ON")
  {
    ps.setDataSetReadyOn(true);
    psc.setSignals(ps);
    dataSetReadyChangedSpy.clear();

    SECTION("It stays ON on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( dataSetReadyChangedSpy.count() == 0 );
    }

    SECTION("when DSR OFF is notified before hold on timed out - UI stays ON")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setDataSetReadyOn(false);
      psc.setSignals(ps);

      REQUIRE( dataSetReadyChangedSpy.count() == 0 );
    }

    SECTION("When DSR OFF is notified - DSR UI goes OFF on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setDataSetReadyOn(false);
      psc.setSignals(ps);
      REQUIRE( dataSetReadyChangedSpy.count() == 0 );

      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( dataSetReadyChangedSpy.count() == 1 );
      CHECK( !dataSetReadyChangedSpy.stateAtIsOn(0) );
    }
  }

  SECTION("When DSR UI became OFF")
  {
    ps.setDataSetReadyOn(true);
    psc.setSignals(ps); // SM: --> on_hold
    psc.setCurrentTime( TimePoint(200ms) );
    ps.setDataSetReadyOn(false);
    psc.setSignals(ps); // SM: --> off_hold
    dataSetReadyChangedSpy.clear();

    ps.setDataSetReadyOn(true);

    SECTION("when DSR ON is notified before hold off timed out - DSR UI stays OFF")
    {
      psc.setCurrentTime( TimePoint(220ms) );

      psc.setSignals(ps);

      REQUIRE( dataSetReadyChangedSpy.count() == 0 );
    }

    SECTION("when DSR ON is notified after hold off timed out - DSR UI goes ON")
    {
      psc.setCurrentTime( TimePoint(250ms) );

      psc.setSignals(ps);

      REQUIRE( dataSetReadyChangedSpy.count() == 1 );
      CHECK( dataSetReadyChangedSpy.stateAtIsOn(0) );
    }
  }
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
}

TEST_CASE("RNG")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);
  PinoutSignalUiStateChangedSignalSpy ringIndicatorChangedSpy(&psc, &TestPinoutSignalsUiController::ringIndicatorChanged);

  SECTION("RNG ON notified - UI goes ON")
  {
    ps.setRingIndicatorOn(true);

    psc.setSignals(ps);

    REQUIRE( ringIndicatorChangedSpy.count() == 1 );
    CHECK( ringIndicatorChangedSpy.stateAtIsOn(0) );
  }

  SECTION("When RNG UI is ON")
  {
    ps.setRingIndicatorOn(true);
    psc.setSignals(ps);
    ringIndicatorChangedSpy.clear();

    SECTION("It stays ON on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( ringIndicatorChangedSpy.count() == 0 );
    }

    SECTION("when RNG OFF is notified before hold on timed out - UI stays ON")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setRingIndicatorOn(false);
      psc.setSignals(ps);

      REQUIRE( ringIndicatorChangedSpy.count() == 0 );
    }

    SECTION("When RNG OFF is notified - RNG UI goes OFF on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setRingIndicatorOn(false);
      psc.setSignals(ps);
      REQUIRE( ringIndicatorChangedSpy.count() == 0 );

      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( ringIndicatorChangedSpy.count() == 1 );
      CHECK( !ringIndicatorChangedSpy.stateAtIsOn(0) );
    }
  }

  SECTION("When RNG UI became OFF")
  {
    ps.setRingIndicatorOn(true);
    psc.setSignals(ps); // SM: --> on_hold
    psc.setCurrentTime( TimePoint(200ms) );
    ps.setRingIndicatorOn(false);
    psc.setSignals(ps); // SM: --> off_hold
    ringIndicatorChangedSpy.clear();

    ps.setRingIndicatorOn(true);

    SECTION("when RNG ON is notified before hold off timed out - RNG UI stays OFF")
    {
      psc.setCurrentTime( TimePoint(220ms) );

      psc.setSignals(ps);

      REQUIRE( ringIndicatorChangedSpy.count() == 0 );
    }

    SECTION("when RNG ON is notified after hold off timed out - RNG UI goes ON")
    {
      psc.setCurrentTime( TimePoint(250ms) );

      psc.setSignals(ps);

      REQUIRE( ringIndicatorChangedSpy.count() == 1 );
      CHECK( ringIndicatorChangedSpy.stateAtIsOn(0) );
    }
  }
}

TEST_CASE("break")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  psc.setHoldOnDuration(100ms);
  psc.setHoldOffDuration(40ms);
  PinoutSignalUiStateChangedSignalSpy breakChangedSpy(&psc, &TestPinoutSignalsUiController::breakChanged);

  SECTION("break ON notified - UI goes ON")
  {
    ps.setBreakOn(true);

    psc.setSignals(ps);

    REQUIRE( breakChangedSpy.count() == 1 );
    CHECK( breakChangedSpy.stateAtIsOn(0) );
  }

  SECTION("When break UI is ON")
  {
    ps.setBreakOn(true);
    psc.setSignals(ps);
    breakChangedSpy.clear();

    SECTION("It stays ON on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( breakChangedSpy.count() == 0 );
    }

    SECTION("when break OFF is notified before hold on timed out - UI stays ON")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setBreakOn(false);
      psc.setSignals(ps);

      REQUIRE( breakChangedSpy.count() == 0 );
    }

    SECTION("When break OFF is notified - break UI goes OFF on wathchdog event after hold on timed out")
    {
      psc.setCurrentTime( TimePoint(20ms) );
      ps.setBreakOn(false);
      psc.setSignals(ps);
      REQUIRE( breakChangedSpy.count() == 0 );

      psc.setCurrentTime( TimePoint(150ms) );
      psc.setWatchdogTimeoutEvent();

      REQUIRE( breakChangedSpy.count() == 1 );
      CHECK( !breakChangedSpy.stateAtIsOn(0) );
    }
  }

  SECTION("When break UI became OFF")
  {
    ps.setBreakOn(true);
    psc.setSignals(ps); // SM: --> on_hold
    psc.setCurrentTime( TimePoint(200ms) );
    ps.setBreakOn(false);
    psc.setSignals(ps); // SM: --> off_hold
    breakChangedSpy.clear();

    ps.setBreakOn(true);

    SECTION("when break ON is notified before hold off timed out - break UI stays OFF")
    {
      psc.setCurrentTime( TimePoint(220ms) );

      psc.setSignals(ps);

      REQUIRE( breakChangedSpy.count() == 0 );
    }

    SECTION("when break ON is notified after hold off timed out - break UI goes ON")
    {
      psc.setCurrentTime( TimePoint(250ms) );

      psc.setSignals(ps);

      REQUIRE( breakChangedSpy.count() == 1 );
      CHECK( breakChangedSpy.stateAtIsOn(0) );
    }
  }
}
