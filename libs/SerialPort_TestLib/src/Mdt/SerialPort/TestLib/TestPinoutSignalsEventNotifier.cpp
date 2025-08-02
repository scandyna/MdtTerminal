// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "TestPinoutSignalsEventNotifier.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace TestLib{

TestPinoutSignalsEventNotifier::TestPinoutSignalsEventNotifier(QObject *parent)
 : AbstractPinoutSignalsEventNotifier(parent)
{
}

void TestPinoutSignalsEventNotifier::setAboutToCloseEvent()
{
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

void TestPinoutSignalsEventNotifier::setBytesAvailable(qint64 count)
{
  assert(count >= 0);

  mBytesAvailable = count;
}

bool TestPinoutSignalsEventNotifier::shouldNotifySignalsChanged() const noexcept
{
  return AbstractPinoutSignalsEventNotifier::shouldNotifySignalsChanged();
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

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
