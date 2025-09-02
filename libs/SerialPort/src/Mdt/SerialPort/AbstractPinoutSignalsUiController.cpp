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
#include <chrono>
#include <cassert>

#include <QDebug>

using namespace std::chrono_literals;


namespace Mdt{ namespace SerialPort{

AbstractPinoutSignalsUiController::AbstractPinoutSignalsUiController(QObject *parent)
 : QObject(parent)
{
  setHoldOnDuration(100ms);
  setHoldOffDuration(40ms);
}

void AbstractPinoutSignalsUiController::setHoldOnDuration(std::chrono::milliseconds d) noexcept
{
  mReceiveDataState.setHoldOnDuration(d);
  mTransmitDataState.setHoldOnDuration(d);
  mDataTerminalReadyState.setHoldOnDuration(d);
  mRequestToSendState.setHoldOnDuration(d);
}

void AbstractPinoutSignalsUiController::setHoldOffDuration(std::chrono::milliseconds d) noexcept
{
  mReceiveDataState.setHoldOffDuration(d);
  mTransmitDataState.setHoldOffDuration(d);
  mDataTerminalReadyState.setHoldOffDuration(d);
  mRequestToSendState.setHoldOffDuration(d);
}

void AbstractPinoutSignalsUiController::setAboutToCloseEvent()
{
  stopWatchdogTimer();

  mReceiveDataState.setStateOffNow();
  mTransmitDataState.setStateOffNow();
  mDataTerminalReadyState.setStateOffNow();
  mRequestToSendState.setStateOffNow();

  notifyChangedStates();
}

void AbstractPinoutSignalsUiController::setSignals(const PinoutSignals & ps)
{
  stopWatchdogTimer();

  // qDebug() << "AbstractPinoutSignalsUiController::setSignals() ...";

  const TimePoint now = getCurrentTime();

  // qDebug() << " now: " << now.time_since_epoch().count();

  // qDebug() << " DTR: " << ps.dataTerminalReadyIsOn();

  mReceiveDataState.setSignalOn(ps.receiveDataIsOn(), now);
  mTransmitDataState.setSignalOn(ps.transmitDataIsOn(), now);
  mDataTerminalReadyState.setSignalOn(ps.dataTerminalReadyIsOn(), now);
  mRequestToSendState.setSignalOn(ps.requestToSendIsOn(), now);

  // qDebug() << " TX UI: " << mTransmitDataState.stateIsOn();

  // qDebug() << " DTR UI state: " << mDataTerminalReadyState.stateIsOn();

  notifyChangedStates();
  startWatchdogTimerIfRequired();

  // if( !watchdogTimerIsActive() ){
  //   startWatchdogTimer();
  // }
}

void AbstractPinoutSignalsUiController::setWatchdogTimeoutEvent()
{
  stopWatchdogTimer();

  // qDebug() << "UI wdt";

  const TimePoint now = getCurrentTime();

  // qDebug() << " now: " << now.time_since_epoch().count();
  // qDebug() << " DTR UI state: " << mDataTerminalReadyState.stateIsOn();

  // qDebug() << " TX UI: " << mTransmitDataState.stateIsOn();
  // qDebug() << " setWatchdogTimeoutEvent() ...";

  mReceiveDataState.setWatchdogTimeoutEvent(now);
  mTransmitDataState.setWatchdogTimeoutEvent(now);
  mDataTerminalReadyState.setWatchdogTimeoutEvent(now);
  mRequestToSendState.setWatchdogTimeoutEvent(now);

  // mTransmitDataState.updateState();
  // if( mTransmitDataState.stateHasChanged() ){
  //   emit transmitDataChanged( mTransmitDataState.stateIsOn() );
  // }

  // mDataTerminalReadyState.updateState();

  // qDebug() << " UI DTR UI state to: " << mDataTerminalReadyState.stateIsOn();

  notifyChangedStates();
  startWatchdogTimerIfRequired();
}

bool AbstractPinoutSignalsUiController::watchdogTimerShouldBeActive() const noexcept
{
  if( mReceiveDataState.watchdogTimerShouldBeActive() ){
    return true;
  }
  if( mTransmitDataState.watchdogTimerShouldBeActive() ){
    return true;
  }
  if( mDataTerminalReadyState.watchdogTimerShouldBeActive() ){
    return true;
  }
  if( mRequestToSendState.watchdogTimerShouldBeActive() ){
    return true;
  }

  return false;
}

void AbstractPinoutSignalsUiController::notifyChangedStates()
{
  if( mReceiveDataState.stateHasChanged() ){
    emit receiveDataChanged( mReceiveDataState.stateIsOn() );
  }
  if( mTransmitDataState.stateHasChanged() ){
    emit transmitDataChanged( mTransmitDataState.stateIsOn() );
  }
  if( mDataTerminalReadyState.stateHasChanged() ){
    emit dataTerminalReadyChanged( mDataTerminalReadyState.stateIsOn() );
  }
  if( mRequestToSendState.stateHasChanged() ){
    emit requestToSendChanged( mRequestToSendState.stateIsOn() );
  }
}

void AbstractPinoutSignalsUiController::startWatchdogTimerIfRequired()
{
  assert( !watchdogTimerIsActive() );

  if( !watchdogTimerShouldBeActive() ){
    return;
  }

  startWatchdogTimer();
}

}} // namespace Mdt{ namespace SerialPort{
