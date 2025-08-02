// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PinoutSignalsUiController.h"
#include <chrono>
#include <cassert>

using namespace std::chrono_literals;

namespace Mdt{ namespace SerialPort{

PinoutSignalsUiController::PinoutSignalsUiController(QObject *parent)
 : AbstractPinoutSignalsUiController(parent)
{
  connect(&mTimer, &QTimer::timeout, this, &PinoutSignalsUiController::setTimerTimeoutEvent);
  mTimer.setTimerType(Qt::CoarseTimer);
  mTimer.setInterval(100ms);
}

void PinoutSignalsUiController::startTimer()
{
  mTimer.start();
}

bool PinoutSignalsUiController::timerIsActive() const
{
  return mTimer.isActive();
}

void PinoutSignalsUiController::stopTimer()
{
  mTimer.stop();
}

}} // namespace Mdt{ namespace SerialPort{
