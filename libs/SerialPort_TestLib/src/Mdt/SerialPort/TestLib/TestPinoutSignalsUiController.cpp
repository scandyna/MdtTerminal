// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "TestPinoutSignalsUiController.h"

namespace Mdt{ namespace SerialPort{ namespace TestLib{

TestPinoutSignalsUiController::TestPinoutSignalsUiController(QObject *parent)
 : AbstractPinoutSignalsUiController(parent)
{
}

void TestPinoutSignalsUiController::setCurrentTime(TimePoint now)
{
  mCurrentTime = now;
}

void TestPinoutSignalsUiController::setWatchdogTimeoutEvent()
{
  AbstractPinoutSignalsUiController::setWatchdogTimeoutEvent();
}

bool TestPinoutSignalsUiController::watchdogTimerShouldBeActive() const noexcept
{
  return AbstractPinoutSignalsUiController::watchdogTimerShouldBeActive();
}

bool TestPinoutSignalsUiController::watchdogTimerIsActive() const
{
  return mTimerIsActive;
}

TestPinoutSignalsUiController::TimePoint TestPinoutSignalsUiController::getCurrentTime() const
{
  return mCurrentTime;
}

void TestPinoutSignalsUiController::startWatchdogTimer()
{
  mTimerIsActive = true;
}

void TestPinoutSignalsUiController::stopWatchdogTimer()
{
  mTimerIsActive = false;
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
