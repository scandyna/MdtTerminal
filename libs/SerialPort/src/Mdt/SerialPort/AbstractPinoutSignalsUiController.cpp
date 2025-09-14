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
  mClearToSendState.setHoldOnDuration(d);
  mDataCarrierDetectState.setHoldOnDuration(d);
  mDataSetReadyState.setHoldOnDuration(d);
  mRingIndicatorState.setHoldOnDuration(d);
  mBreakState.setHoldOnDuration(d);
}

void AbstractPinoutSignalsUiController::setHoldOffDuration(std::chrono::milliseconds d) noexcept
{
  mReceiveDataState.setHoldOffDuration(d);
  mTransmitDataState.setHoldOffDuration(d);
  mDataTerminalReadyState.setHoldOffDuration(d);
  mRequestToSendState.setHoldOffDuration(d);
  mClearToSendState.setHoldOffDuration(d);
  mDataCarrierDetectState.setHoldOffDuration(d);
  mDataSetReadyState.setHoldOffDuration(d);
  mRingIndicatorState.setHoldOffDuration(d);
  mBreakState.setHoldOffDuration(d);
}

void AbstractPinoutSignalsUiController::setAboutToCloseEvent()
{
  stopWatchdogTimer();

  mReceiveDataState.setStateOffNow();
  mTransmitDataState.setStateOffNow();
  mDataTerminalReadyState.setStateOffNow();
  mRequestToSendState.setStateOffNow();
  mClearToSendState.setStateOffNow();
  mDataCarrierDetectState.setStateOffNow();
  mDataSetReadyState.setStateOffNow();
  mRingIndicatorState.setStateOffNow();
  mBreakState.setStateOffNow();

  notifyChangedStates();
}

void AbstractPinoutSignalsUiController::setSignals(const PinoutSignals & ps)
{
  stopWatchdogTimer();

  const TimePoint now = getCurrentTime();

  mReceiveDataState.setSignalOn(ps.receiveDataIsOn(), now);
  mTransmitDataState.setSignalOn(ps.transmitDataIsOn(), now);
  mRequestToSendState.setSignalOn(ps.requestToSendIsOn(), now);
  mClearToSendState.setSignalOn(ps.clearToSendIsOn(), now);
  mDataCarrierDetectState.setSignalOn(ps.dataCarrierDetectIsOn(), now);
  mDataSetReadyState.setSignalOn(ps.dataSetReadyIsOn(), now);
  mDataTerminalReadyState.setSignalOn(ps.dataTerminalReadyIsOn(), now);
  mRingIndicatorState.setSignalOn(ps.ringIndicatorIsOn(), now);
  mBreakState.setSignalOn(ps.breakIsOn(), now);

  notifyChangedStates();
  startWatchdogTimerIfRequired();
}

void AbstractPinoutSignalsUiController::setWatchdogTimeoutEvent()
{
  stopWatchdogTimer();

  const TimePoint now = getCurrentTime();

  mReceiveDataState.setWatchdogTimeoutEvent(now);
  mTransmitDataState.setWatchdogTimeoutEvent(now);
  mDataTerminalReadyState.setWatchdogTimeoutEvent(now);
  mRequestToSendState.setWatchdogTimeoutEvent(now);
  mClearToSendState.setWatchdogTimeoutEvent(now);
  mDataCarrierDetectState.setWatchdogTimeoutEvent(now);
  mDataSetReadyState.setWatchdogTimeoutEvent(now);
  mRingIndicatorState.setWatchdogTimeoutEvent(now);
  mBreakState.setWatchdogTimeoutEvent(now);

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
  if( mClearToSendState.watchdogTimerShouldBeActive() ){
    return true;
  }
  if( mDataCarrierDetectState.watchdogTimerShouldBeActive() ){
    return true;
  }
  if( mDataSetReadyState.watchdogTimerShouldBeActive() ){
    return true;
  }
  if( mRingIndicatorState.watchdogTimerShouldBeActive() ){
    return true;
  }
  if( mBreakState.watchdogTimerShouldBeActive() ){
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
  if( mRequestToSendState.stateHasChanged() ){
    emit requestToSendChanged( mRequestToSendState.stateIsOn() );
  }
  if( mClearToSendState.stateHasChanged() ){
    emit clearToSendChanged( mClearToSendState.stateIsOn() );
  }
  if( mDataCarrierDetectState.stateHasChanged() ){
    emit dataCarrierDetectChanged( mDataCarrierDetectState.stateIsOn() );
  }
  if( mDataSetReadyState.stateHasChanged() ){
    emit dataSetReadyChanged( mDataSetReadyState.stateIsOn() );
  }
  if( mDataTerminalReadyState.stateHasChanged() ){
    emit dataTerminalReadyChanged( mDataTerminalReadyState.stateIsOn() );
  }
  if( mRingIndicatorState.stateHasChanged() ){
    emit ringIndicatorChanged( mRingIndicatorState.stateIsOn() );
  }
  if( mBreakState.stateHasChanged() ){
    emit breakChanged( mBreakState.stateIsOn() );
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
