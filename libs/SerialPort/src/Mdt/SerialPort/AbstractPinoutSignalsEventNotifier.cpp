// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
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
  /*
   * Bug GL-5
   * https://gitlab.com/scandyna/mdtterminal/-/work_items/5
   *
   * By calling functions that processes events (event loop),
   * the port can be closed.
   * setAboutToCloseEvent() will be called, and stops the timer.
   * Then, we re-enter this method, and we start the timer again.
   * We must make sure:
   * - To stop the timer in all cases
   * - Do not restart the timer when the port has been closed.
   */
  stopTimer();
  if( !portIsOpen() ){
    return;
  }

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
  assert( portIsOpen() );

  mCurrentPinoutSignals.setSignals( readPinoutSignals() );
}

void AbstractPinoutSignalsEventNotifier::startTimer()
{
  if( portIsOpen() ){
   doStartTimer();
  }
}

}} // namespace Mdt{ namespace SerialPort{
