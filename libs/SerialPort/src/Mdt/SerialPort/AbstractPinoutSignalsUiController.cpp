// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "AbstractPinoutSignalsUiController.h"

namespace Mdt{ namespace SerialPort{

AbstractPinoutSignalsUiController::AbstractPinoutSignalsUiController(QObject *parent)
 : QObject(parent)
{
}

void AbstractPinoutSignalsUiController::setAboutToCloseEvent()
{
  stopTimer();
}

void AbstractPinoutSignalsUiController::setSignals(const PinoutSignals & ps)
{
  mReceiveDataState.setSignalOn( ps.receiveDataIsOn() );

  if( !timerIsActive() ){
    startTimer();
  }
}

void AbstractPinoutSignalsUiController::setTimerTimeoutEvent()
{
  mReceiveDataState.updateState();
  if( mReceiveDataState.stateHasChanged() ){
    emit receiveDataChanged( mReceiveDataState.stateIsOn() );
  }
}

}} // namespace Mdt{ namespace SerialPort{
