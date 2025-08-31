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
  readAndUpdatePinoutSignalsStates();
  notifySignalsIfChanged();
  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setAboutToCloseEvent()
{
  stopTimer();
  mPreviousPinoutSignals.clear();
  mCurrentPinoutSignals.clear();
}

void AbstractPinoutSignalsEventNotifier::setTimerTimeoutEvent()
{
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  updateReceiveDataState();
  updateTransmitDataState();
  readAndUpdatePinoutSignalsStates();

  notifySignalsIfChanged();
  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setReadyReadEvent()
{
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  mCurrentPinoutSignals.setReceiveDataOn(true);

  updateTransmitDataState();
  readAndUpdatePinoutSignalsStates();

  /// \todo Also read other pinout signals - add heler
  
  /// handleCommonEvents() ?
  

  notifySignalsIfChanged();
  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setBytesWrittenEvent(qint64 /*bytes*/)
{
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  // qDebug() << "setBytesWrittenEvent() - bytes written: " << bytes;

  mCurrentPinoutSignals.setTransmitDataOn(true);

  updateReceiveDataState();
  readAndUpdatePinoutSignalsStates();

  /// \todo Also read other pinout signals - add heler
  
  /// handleCommonEvents() ?
  

  notifySignalsIfChanged();
  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setDataTerminalReadyChangedEvent(bool set)
{
  // qDebug() << "setDataTerminalReadyChangedEvent() : " << set;

  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  mCurrentPinoutSignals.setDataTerminalReadyOn(set);

  /// \todo Also read other pinout signals - add heler
  
  /// handleCommonEvents() ?
  

  notifySignalsIfChanged();
  startTimer();
}

bool AbstractPinoutSignalsEventNotifier::shouldNotifySignalsChanged() const noexcept
{
  return mCurrentPinoutSignals != mPreviousPinoutSignals;
}

void AbstractPinoutSignalsEventNotifier::notifySignalsIfChanged() const
{
  if( shouldNotifySignalsChanged() ){
    emit signalsChanged(mCurrentPinoutSignals);
  }
}

void AbstractPinoutSignalsEventNotifier::updateReceiveDataState()
{
  assert( !timerIsActive() );

  mCurrentPinoutSignals.setReceiveDataOn(bytesAvailable() > 0);
}

void AbstractPinoutSignalsEventNotifier::updateTransmitDataState()
{
  assert( !timerIsActive() );

  if( bytesToWrite() > 0 ){
    qDebug() << "bytesToWrite: " << bytesToWrite();
  }

  mCurrentPinoutSignals.setTransmitDataOn(bytesToWrite() > 0);
}

void AbstractPinoutSignalsEventNotifier::readAndUpdatePinoutSignalsStates()
{
  assert( !timerIsActive() );

  mCurrentPinoutSignals.setSignals( readPinoutSignals() );
}

}} // namespace Mdt{ namespace SerialPort{
