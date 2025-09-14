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

  notifySignalsIfChanged();
  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setBytesWrittenEvent(qint64 /*bytes*/)
{
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  mCurrentPinoutSignals.setTransmitDataOn(true);

  updateReceiveDataState();
  readAndUpdatePinoutSignalsStates();

  notifySignalsIfChanged();
  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setDataTerminalReadyChangedEvent(bool set)
{
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  mCurrentPinoutSignals.setDataTerminalReadyOn(set);

  /// \todo Also read other pinout signals and RX TX ?

  notifySignalsIfChanged();
  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setRequestToSendChangedEvent(bool set)
{
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  mCurrentPinoutSignals.setRequestToSendOn(set);

  /// \todo Also read other pinout signals and RX TX ?

  notifySignalsIfChanged();
  startTimer();
}

void AbstractPinoutSignalsEventNotifier::setBreakEnabledChangedEvent(bool set)
{
  stopTimer();
  mPreviousPinoutSignals = mCurrentPinoutSignals;

  mCurrentPinoutSignals.setBreakOn(set);

  /// \todo Also read other pinout signals and RX TX ?

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

  mCurrentPinoutSignals.setTransmitDataOn(bytesToWrite() > 0);
}

void AbstractPinoutSignalsEventNotifier::readAndUpdatePinoutSignalsStates()
{
  assert( !timerIsActive() );

  mCurrentPinoutSignals.setSignals( readPinoutSignals() );
}

}} // namespace Mdt{ namespace SerialPort{
