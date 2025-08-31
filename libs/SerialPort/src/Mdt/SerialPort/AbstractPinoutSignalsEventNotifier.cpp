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
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  /// \todo maybe, otherwise set true ??
  if( bytesAvailable() <= 0 ){
    mCurrentPinoutSignals.setReceiveDataOn(false);
  }
  if( bytesToWrite() <= 0 ){
    mCurrentPinoutSignals.setTransmitDataOn(false);
  }

  // qDebug() << "TO - PO sigs: " << readPinoutSignals();
  // qDebug() << " DTR: " << mCurrentPinoutSignals.dataTerminalReadyIsOn();
  
  /// \todo Also read other pinout signals - add heler
  
  /// handleCommonEvents() ?

  /// \todo check if something changed - add helper

  if( shouldNotifySignalsChanged() ){
    emit signalsChanged(mCurrentPinoutSignals);
  }

  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setReadyReadEvent()
{
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  mCurrentPinoutSignals.setReceiveDataOn(true);

  /// \todo Also read other pinout signals - add heler
  
  /// handleCommonEvents() ?
  

  /// \todo check if something changed - add helper

  if( shouldNotifySignalsChanged() ){
    emit signalsChanged(mCurrentPinoutSignals);
  }

  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setBytesWrittenEvent(qint64 /*bytes*/)
{
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  mCurrentPinoutSignals.setTransmitDataOn(true);

  /// \todo Also read other pinout signals - add heler
  
  /// handleCommonEvents() ?
  

  /// \todo check if something changed - add helper

  if( shouldNotifySignalsChanged() ){
    emit signalsChanged(mCurrentPinoutSignals);
  }

  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setDataTerminalReadyChangedEvent(bool set)
{
  qDebug() << "setDataTerminalReadyChangedEvent() : " << set;

  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  mCurrentPinoutSignals.setDataTerminalReadyOn(set);

  /// \todo Also read other pinout signals - add heler
  
  /// handleCommonEvents() ?
  

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

void AbstractPinoutSignalsEventNotifier::updateReceiveDataState()
{
  assert( !timerIsActive() );
}

}} // namespace Mdt{ namespace SerialPort{
