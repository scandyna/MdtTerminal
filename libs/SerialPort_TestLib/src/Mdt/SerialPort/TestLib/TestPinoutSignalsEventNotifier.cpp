// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "TestPinoutSignalsEventNotifier.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace TestLib{

TestPinoutSignalsEventNotifier::TestPinoutSignalsEventNotifier(QObject *parent)
 : AbstractPinoutSignalsEventNotifier(parent)
{
}

void TestPinoutSignalsEventNotifier::setPortOpen()
{
  mPortIsOpen = true;
  AbstractPinoutSignalsEventNotifier::setPortOpen();
}

void TestPinoutSignalsEventNotifier::setAboutToCloseEvent()
{
  mPortIsOpen = false;
  AbstractPinoutSignalsEventNotifier::setAboutToCloseEvent();
}

void TestPinoutSignalsEventNotifier::setTimerTimeoutEvent()
{
  AbstractPinoutSignalsEventNotifier::setTimerTimeoutEvent();
}

void TestPinoutSignalsEventNotifier::setReadyReadEvent()
{
  AbstractPinoutSignalsEventNotifier::setReadyReadEvent();
}

void TestPinoutSignalsEventNotifier::setBytesWrittenEvent(qint64 bytes)
{
  AbstractPinoutSignalsEventNotifier::setBytesWrittenEvent(bytes);
}

void TestPinoutSignalsEventNotifier::setDataTerminalReadyChangedEvent(bool set)
{
  AbstractPinoutSignalsEventNotifier::setDataTerminalReadyChangedEvent(set);
}

void TestPinoutSignalsEventNotifier::setRequestToSendChangedEvent(bool set)
{
  AbstractPinoutSignalsEventNotifier::setRequestToSendChangedEvent(set);
}

void TestPinoutSignalsEventNotifier::setBreakEnabledChangedEvent(bool set)
{
  AbstractPinoutSignalsEventNotifier::setBreakEnabledChangedEvent(set);
}

void TestPinoutSignalsEventNotifier::setBytesAvailable(qint64 count)
{
  assert(count >= 0);

  mBytesAvailable = count;
}

void TestPinoutSignalsEventNotifier::setBytesToWrite(qint64 count)
{
  assert(count >= 0);

  mBytesToWrite = count;
}

void TestPinoutSignalsEventNotifier::setPortPinoutSignals(QSerialPort::PinoutSignals ps)
{
  mPortPinoutSignals = ps;
}

bool TestPinoutSignalsEventNotifier::shouldNotifySignalsChanged() const noexcept
{
  return AbstractPinoutSignalsEventNotifier::shouldNotifySignalsChanged();
}

void TestPinoutSignalsEventNotifier::updateReceiveDataState()
{
  AbstractPinoutSignalsEventNotifier::updateReceiveDataState();
}

void TestPinoutSignalsEventNotifier::updateTransmitDataState()
{
  AbstractPinoutSignalsEventNotifier::updateTransmitDataState();
}

void TestPinoutSignalsEventNotifier::readAndUpdatePinoutSignalsStates()
{
  AbstractPinoutSignalsEventNotifier::readAndUpdatePinoutSignalsStates();
}

bool TestPinoutSignalsEventNotifier::portIsOpen() const
{
  return mPortIsOpen;
}

bool TestPinoutSignalsEventNotifier::timerIsActive() const
{
  return mTimerIsActive;
}

void TestPinoutSignalsEventNotifier::startTimer()
{
  mTimerIsActive = true;
}

void TestPinoutSignalsEventNotifier::stopTimer()
{
  mTimerIsActive = false;
}

qint64 TestPinoutSignalsEventNotifier::bytesAvailable() const
{
  return mBytesAvailable;
}

qint64 TestPinoutSignalsEventNotifier::bytesToWrite() const
{
  return mBytesToWrite;
}

QSerialPort::PinoutSignals TestPinoutSignalsEventNotifier::readPinoutSignals()
{
  return mPortPinoutSignals;
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
