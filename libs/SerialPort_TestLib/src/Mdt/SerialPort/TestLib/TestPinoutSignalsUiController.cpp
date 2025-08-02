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

void TestPinoutSignalsUiController::setTimerTimeoutEvent()
{
  AbstractPinoutSignalsUiController::setTimerTimeoutEvent();
}

// bool TestPinoutSignalsUiController::deduceReceiveDataState() const noexcept
// {
//   return AbstractPinoutSignalsUiController::deduceReceiveDataState();
// }

// bool TestPinoutSignalsUiController::shouldNotifyReceiveDataChanged() const noexcept
// {
//   return AbstractPinoutSignalsUiController::shouldNotifyReceiveDataChanged();
// }

bool TestPinoutSignalsUiController::timerIsActive() const
{
  return mTimerIsActive;
}

void TestPinoutSignalsUiController::startTimer()
{
  mTimerIsActive = true;
}

void TestPinoutSignalsUiController::stopTimer()
{
  mTimerIsActive = false;
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
