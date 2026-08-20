// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsEditorStateMachine.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

SettingsEditorStateMachine::SettingsEditorStateMachine(QObject *parent)
 : QObject(parent)
{
}

void SettingsEditorStateMachine::start()
{
  emit currentStateChanged(mCurrentState);
}

void SettingsEditorStateMachine::setStartFetchingSystemInfoEvent()
{
  switch( currentEnumState() ){
    case StateEnum::Incomplete:
      transitFrom_Incomplete_to_FetchingSystemInfo();
      break;
    case StateEnum::Complete:
      transitFrom_Complete_to_FetchingSystemInfo();
      break;
    case StateEnum::FetchingSystemInfo:
      break;
  }
}

void SettingsEditorStateMachine::setSettingsCompleteEvent()
{
  switch( currentEnumState() ){
    case StateEnum::Incomplete:
      transitFrom_Incomplete_to_Complete();
      break;
    case StateEnum::Complete:
      break;
    case StateEnum::FetchingSystemInfo:
      transitFrom_FetchingSystemInfo_to_Complete();
      break;
  }
}

void SettingsEditorStateMachine::setSettingsIncompleteEvent()
{
  switch( currentEnumState() ){
    case StateEnum::Incomplete:
      break;
    case StateEnum::Complete:
      transitFrom_Complete_to_Incomplete();
      break;
    case StateEnum::FetchingSystemInfo:
      transitFrom_FetchingSystemInfo_to_Incomplete();
      break;
  }
}

void SettingsEditorStateMachine::transitFrom_Incomplete_to_Complete()
{
  assert(currentEnumState() == StateEnum::Incomplete);

  updateAndNotifyNewState( SettingsEditorState::complete() );
}

void SettingsEditorStateMachine::transitFrom_Incomplete_to_FetchingSystemInfo()
{
  assert(currentEnumState() == StateEnum::Incomplete);

  updateAndNotifyNewState( SettingsEditorState::fetchingSystemInfo() );
}

void SettingsEditorStateMachine::transitFrom_Complete_to_Incomplete()
{
  assert(currentEnumState() == StateEnum::Complete);

  updateAndNotifyNewState( SettingsEditorState::incomplete() );
}

void SettingsEditorStateMachine::transitFrom_Complete_to_FetchingSystemInfo()
{
  assert(currentEnumState() == StateEnum::Complete);

  updateAndNotifyNewState( SettingsEditorState::fetchingSystemInfo() );
}

void SettingsEditorStateMachine::transitFrom_FetchingSystemInfo_to_Incomplete()
{
  assert(currentEnumState() == StateEnum::FetchingSystemInfo);

  updateAndNotifyNewState( SettingsEditorState::incomplete() );
}

void SettingsEditorStateMachine::transitFrom_FetchingSystemInfo_to_Complete()
{
  assert(currentEnumState() == StateEnum::FetchingSystemInfo);

  updateAndNotifyNewState( SettingsEditorState::complete() );
}

void SettingsEditorStateMachine::updateAndNotifyNewState(const SettingsEditorState & state)
{
  mCurrentState = state;
  emit currentStateChanged(mCurrentState);
}

}} // namespace Mdt{ namespace SerialPort{
