// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsEditorStateChangedSignalSpy.h"

using namespace Mdt::SerialPort;


SettingsEditorStateChangedSignalSpy::SettingsEditorStateChangedSignalSpy(SettingsEditorStateMachine *sm, QObject *parent)
 : QObject(parent)
{
  assert(sm != nullptr);

  connect(sm, &SettingsEditorStateMachine::currentStateChanged, this, &SettingsEditorStateChangedSignalSpy::appendStateChanged);
}

void SettingsEditorStateChangedSignalSpy::clear() noexcept
{
  mStateList.clear();
}

void SettingsEditorStateChangedSignalSpy::appendStateChanged(const SettingsEditorState & state)
{
  mStateList.push_back( state.enumState() );
}
