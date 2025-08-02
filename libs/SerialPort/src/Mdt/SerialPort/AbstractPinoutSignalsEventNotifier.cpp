// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "AbstractPinoutSignalsEventNotifier.h"
#include <cassert>

#include <QDebug>

namespace Mdt{ namespace SerialPort{

AbstractPinoutSignalsEventNotifier::AbstractPinoutSignalsEventNotifier(QObject *parent)
 : QObject(parent)
{
}

void AbstractPinoutSignalsEventNotifier::setPortOpen()
{
  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setAboutToCloseEvent()
{
  stopTimer();
}

void AbstractPinoutSignalsEventNotifier::setTimerTimeoutEvent()
{
  qDebug() << "timer tiemout ...";

  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  qDebug() << " bytesAvailable: " << bytesAvailable();
  
  if( bytesAvailable() <= 0 ){
    mCurrentPinoutSignals.setReceiveDataOn(false);
  }

  /// \todo Also read other pinout signals - add heler
  

  /// \todo check if something changed - add helper

  if( shouldNotifySignalsChanged() ){
    emit signalsChanged(mCurrentPinoutSignals);
  }

  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setReadyReadEvent()
{
  qDebug() << "ready read ...";

  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;
  
  qDebug() << " bytesAvailable: " << bytesAvailable();

  mCurrentPinoutSignals.setReceiveDataOn(true);

  /// \todo Also read other pinout signals - add heler
  

  /// \todo check if something changed - add helper

  if( shouldNotifySignalsChanged() ){
    emit signalsChanged(mCurrentPinoutSignals);
  }

  startTimer();
}

bool AbstractPinoutSignalsEventNotifier::shouldNotifySignalsChanged() const noexcept
{
  return mCurrentPinoutSignals != mPreviousPinoutSignals;
}

}} // namespace Mdt{ namespace SerialPort{
