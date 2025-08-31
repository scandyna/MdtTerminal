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
  // qDebug() << "setPortOpen() ...";

  readAndUpdatePinoutSignalsStates();
  notifySignalsIfChanged();
  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setAboutToCloseEvent()
{
  // qDebug() << "setAboutToCloseEvent() ...";

  stopTimer();
  mPreviousPinoutSignals.clear();
  mCurrentPinoutSignals.clear();
}

void AbstractPinoutSignalsEventNotifier::setTimerTimeoutEvent()
{
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  /// \todo maybe, otherwise set true ??
  updateReceiveDataState();
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

void AbstractPinoutSignalsEventNotifier::notifySignalsIfChanged() const
{
  // qDebug() << "notifySignalsIfChanged()...";
  // qDebug() << " cur DTR: " << mCurrentPinoutSignals.dataTerminalReadyIsOn();
  // qDebug() << " prev DTR: " << mPreviousPinoutSignals.dataTerminalReadyIsOn();
  // qDebug() << " should notify: " << shouldNotifySignalsChanged();

  if( shouldNotifySignalsChanged() ){
    emit signalsChanged(mCurrentPinoutSignals);
  }
}

void AbstractPinoutSignalsEventNotifier::updateReceiveDataState()
{
  assert( !timerIsActive() );

  mCurrentPinoutSignals.setReceiveDataOn(bytesAvailable() > 0);
}

void AbstractPinoutSignalsEventNotifier::readAndUpdatePinoutSignalsStates()
{
  assert( !timerIsActive() );

  mCurrentPinoutSignals.setSignals( readPinoutSignals() );

  // qDebug() << "readAndUpdatePinoutSignalsStates() - DTR: " << mCurrentPinoutSignals.dataTerminalReadyIsOn();
}

}} // namespace Mdt{ namespace SerialPort{
