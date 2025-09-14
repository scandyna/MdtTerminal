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

TEST_CASE("readAndUpdatePinoutSignalsStates")
{
  TestPinoutSignalsEventNotifier psn;
  QSerialPort::PinoutSignals qps;

  SECTION("DTR ON")
  {
    qps.setFlag(QSerialPort::DataTerminalReadySignal, true);
    psn.setPortPinoutSignals(qps);

    psn.readAndUpdatePinoutSignalsStates();

    CHECK( psn.currentSignals().dataTerminalReadyIsOn() );
  }

  SECTION("RTS ON")
  {
    qps.setFlag(QSerialPort::RequestToSendSignal, true);
    psn.setPortPinoutSignals(qps);

    psn.readAndUpdatePinoutSignalsStates();

    CHECK( psn.currentSignals().requestToSendIsOn() );
  }
}

TEST_CASE("openReads_DTR_AndNotifiesIfON")
{
  TestPinoutSignalsEventNotifier psn;
  QSerialPort::PinoutSignals qps;

  qps.setFlag(QSerialPort::DataTerminalReadySignal, true);
  psn.setPortPinoutSignals(qps);

  psn.setPortOpen();

  CHECK( psn.shouldNotifySignalsChanged() );
  CHECK( psn.currentSignals().dataTerminalReadyIsOn() );

  // Produce a timer timout event - so previous states is updated
  psn.setTimerTimeoutEvent();

  psn.setAboutToCloseEvent();

  psn.setPortOpen();

  CHECK( psn.shouldNotifySignalsChanged() );
  CHECK( psn.currentSignals().dataTerminalReadyIsOn() );
}

TEST_CASE("updateReceiveDataState")
{
  TestPinoutSignalsEventNotifier psn;
  REQUIRE( !psn.currentSignals().receiveDataIsOn() );

  psn.setBytesAvailable(10);
  psn.updateReceiveDataState();
  CHECK( psn.currentSignals().receiveDataIsOn() );

  psn.setBytesAvailable(0);
  psn.updateReceiveDataState();
  CHECK( !psn.currentSignals().receiveDataIsOn() );
}

TEST_CASE("updateTransmitDataState")
{
  TestPinoutSignalsEventNotifier psn;
  REQUIRE( !psn.currentSignals().transmitDataIsOn() );

  psn.setBytesToWrite(10);
  psn.updateTransmitDataState();
  CHECK( psn.currentSignals().transmitDataIsOn() );

  psn.setBytesToWrite(0);
  psn.updateTransmitDataState();
  CHECK( !psn.currentSignals().transmitDataIsOn() );
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

TEST_CASE("bytesWritten_sets_TX_ON_then_OFF_when_NoBytesToWrite")
{
  TestPinoutSignalsEventNotifier psn;

  psn.setBytesToWrite(10);
  psn.setBytesWrittenEvent(5);

  CHECK( psn.currentSignals().transmitDataIsOn() );
  CHECK( psn.shouldNotifySignalsChanged() );

  psn.setBytesToWrite(5);
  psn.setTimerTimeoutEvent();

  CHECK( psn.currentSignals().transmitDataIsOn() );
  CHECK( !psn.shouldNotifySignalsChanged() );

  psn.setBytesWrittenEvent(5);

  CHECK( psn.currentSignals().transmitDataIsOn() );
  CHECK( !psn.shouldNotifySignalsChanged() );

  psn.setBytesToWrite(0);
  psn.setTimerTimeoutEvent();

  CHECK( !psn.currentSignals().transmitDataIsOn() );
  CHECK( psn.shouldNotifySignalsChanged() );
}

TEST_CASE("DTR_changedEvent")
{
  TestPinoutSignalsEventNotifier psn;

  psn.setDataTerminalReadyChangedEvent(true);

  CHECK( psn.currentSignals().dataTerminalReadyIsOn() );
  CHECK( psn.shouldNotifySignalsChanged() );
}

TEST_CASE("RTS_changedEvent")
{
  TestPinoutSignalsEventNotifier psn;

  psn.setRequestToSendChangedEvent(true);

  CHECK( psn.currentSignals().requestToSendIsOn() );
  CHECK( psn.shouldNotifySignalsChanged() );
}

TEST_CASE("Break_changedEvent")
{
  TestPinoutSignalsEventNotifier psn;

  psn.setBreakEnabledChangedEvent(true);

  CHECK( psn.currentSignals().breakIsOn() );
  CHECK( psn.shouldNotifySignalsChanged() );
}
