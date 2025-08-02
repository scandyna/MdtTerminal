// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/TestLib/TestPinoutSignalsEventNotifier.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::SerialPort::TestLib::TestPinoutSignalsEventNotifier;


TEST_CASE("initialState")
{
  TestPinoutSignalsEventNotifier psn;

  CHECK( !psn.timerIsActive() );
  CHECK( !psn.shouldNotifySignalsChanged() );
}

TEST_CASE("openClose")
{
  TestPinoutSignalsEventNotifier psn;
  CHECK( !psn.timerIsActive() );

  psn.setPortOpen();
  CHECK( psn.timerIsActive() );

  psn.setAboutToCloseEvent();
  CHECK( !psn.timerIsActive() );
}

TEST_CASE("readyRead_sets_RX_ON_then_OFF_whenNoBytesAvailable")
{
  TestPinoutSignalsEventNotifier psn;

  psn.setBytesAvailable(10);
  psn.setReadyReadEvent();

  CHECK( psn.currentSignals().receiveDataIsOn() );
  CHECK( psn.shouldNotifySignalsChanged() );

  psn.setBytesAvailable(5);
  psn.setTimerTimeoutEvent();

  CHECK( psn.currentSignals().receiveDataIsOn() );
  CHECK( !psn.shouldNotifySignalsChanged() );

  psn.setBytesAvailable(0);
  psn.setTimerTimeoutEvent();

  CHECK( !psn.currentSignals().receiveDataIsOn() );
  CHECK( psn.shouldNotifySignalsChanged() );
}
