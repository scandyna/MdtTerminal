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

#include <QDebug>

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
  qDebug() << "AbstractPinoutSignalsUiController::setSignals() ...";
  qDebug() << " UI DTR: " << ps.dataTerminalReadyIsOn();

  // mReceiveDataState.setSignalOn( ps.receiveDataIsOn() );
  // mTransmitDataState.setSignalOn( ps.transmitDataIsOn() );
  // mDataTerminalReadyState.setSignalOn( ps.dataTerminalReadyIsOn() );
  
  // qDebug() << " UI DTR UI state: " << mDataTerminalReadyState.stateIsOn();

  if( !timerIsActive() ){
    startTimer();
  }
}

void AbstractPinoutSignalsUiController::setTimerTimeoutEvent()
{
  qDebug() << "UI TO";
  
  // mReceiveDataState.updateState();
  if( mReceiveDataState.stateHasChanged() ){
    emit receiveDataChanged( mReceiveDataState.stateIsOn() );
  }

  // mTransmitDataState.updateState();
  if( mTransmitDataState.stateHasChanged() ){
    emit transmitDataChanged( mTransmitDataState.stateIsOn() );
  }

  // mDataTerminalReadyState.updateState();
  if( mDataTerminalReadyState.stateHasChanged() ){
    emit dataTerminalReadyChanged( mDataTerminalReadyState.stateIsOn() );
  }
  
  qDebug() << " UI DTR UI state to: " << mDataTerminalReadyState.stateIsOn();
}

}} // namespace Mdt{ namespace SerialPort{
