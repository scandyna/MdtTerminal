// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "MainWindowStateChangedSignalSpy.h"
#include <cassert>

MainWindowStateChangedSignalSpy::MainWindowStateChangedSignalSpy(MainWindowStateMachine *sm, QObject *parent)
 : QObject(parent)
{
  assert(sm != nullptr);

  connect(sm, &MainWindowStateMachine::currentStateChanged, this, &MainWindowStateChangedSignalSpy::appendStateChanged);
}

MainWindowStateChangedSignalSpy::StateEnum MainWindowStateChangedSignalSpy::enumStateAt(size_t index) const noexcept
{
  assert( index < count() );

  return mStateList[index];
}

void MainWindowStateChangedSignalSpy::clear() noexcept
{
  mStateList.clear();
}

void MainWindowStateChangedSignalSpy::appendStateChanged(const MainWindowState & state)
{
  mStateList.push_back( state.enumState() );
}
