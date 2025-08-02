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

using namespace Mdt::SerialPort;
using Mdt::SerialPort::TestLib::TestPinoutSignalsUiController;
using Mdt::SerialPort::TestLib::PinoutSignalUiStateChangedSignalSpy;


TEST_CASE("initialState")
{
  TestPinoutSignalsUiController psc;

  CHECK( !psc.timerIsActive() );
  // CHECK( psc.deduceReceiveDataState() == false );
  // CHECK( !psc.shouldNotifyReceiveDataChanged() );
}

TEST_CASE("firstEventStartsTimer_CloseStopsTimer")
{
  TestPinoutSignalsUiController psc;
  REQUIRE( !psc.timerIsActive() );

  PinoutSignals ps;
  psc.setSignals(ps);

  CHECK( psc.timerIsActive() );

  psc.setAboutToCloseEvent();

  CHECK( !psc.timerIsActive() );
}

TEST_CASE("RX")
{
  PinoutSignals ps;
  TestPinoutSignalsUiController psc;
  PinoutSignalUiStateChangedSignalSpy receiveDataChangedSpy(&psc, &TestPinoutSignalsUiController::receiveDataChanged);

  // REQUIRE( psc.deduceReceiveDataState() == false );
  // REQUIRE( !psc.shouldNotifyReceiveDataChanged() );

  SECTION("only 1 RX ON notified")
  {
    ps.setReceiveDataOn(true);

    psc.setSignals(ps);

    psc.setTimerTimeoutEvent();

    REQUIRE( receiveDataChangedSpy.count() == 1 );
    CHECK( receiveDataChangedSpy.stateAtIsOn(0) );
  }
}
