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
  mReceiveDataState.setSignalOn( ps.receiveDataIsOn() );
  // if( ps.receiveDataIsOn() ){
  //   ++mRxOnCount;
  // }

  if( !timerIsActive() ){
    startTimer();
  }
}

void AbstractPinoutSignalsUiController::setTimerTimeoutEvent()
{
  qDebug() << "UI timer timeout ..";

  mReceiveDataState.updateState();
  if( mReceiveDataState.stateHasChanged() ){
    emit receiveDataChanged( mReceiveDataState.stateIsOn() );
  }

//   mCurrentUiRx = deduceReceiveDataState();
//   
//   mRxOnCount = 0;
//   
//   qDebug() << " mCurrentUiRx: " << mCurrentUiRx;
//   qDebug() << " mPreviousUiRx: " << mPreviousUiRx;
//   
//   if( shouldNotifyReceiveDataChanged() ){
//     mPreviousUiRx = mCurrentUiRx;
//     emit receiveDataChanged(mCurrentUiRx);
//   }
}

// bool AbstractPinoutSignalsUiController::deduceReceiveDataState() const noexcept
// {
//   return mRxOnCount > 0;
// }

// bool AbstractPinoutSignalsUiController::shouldNotifyReceiveDataChanged() const noexcept
// {
//   qDebug() << " shouldNotify: mCurrentUiRx: " << mCurrentUiRx;
//   qDebug() << " shouldNotify: mPreviousUiRx: " << mPreviousUiRx;
// 
//   return mCurrentUiRx != mPreviousUiRx;
// }

}} // namespace Mdt{ namespace SerialPort{
