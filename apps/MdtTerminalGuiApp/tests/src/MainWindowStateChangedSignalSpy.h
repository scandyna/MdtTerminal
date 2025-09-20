// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MAIN_WINDOW_STATE_CHANGED_SIGNAL_SPY_H
#define MAIN_WINDOW_STATE_CHANGED_SIGNAL_SPY_H

#include "MainWindowStateMachine.h"
#include <QObject>
#include <vector>

class MainWindowStateChangedSignalSpy : public QObject
{
  Q_OBJECT

 public:

  using StateEnum = MainWindowState::StateEnum;

  explicit
  MainWindowStateChangedSignalSpy(MainWindowStateMachine *sm, QObject *parent = nullptr);

  size_t count() const noexcept
  {
    return mStateList.size();
  }

  StateEnum enumStateAt(size_t index) const noexcept;

  void clear() noexcept;

 private Q_SLOTS:

  void appendStateChanged(const MainWindowState & state);

 private:

  std::vector<StateEnum> mStateList;
};

#endif // #ifndef MAIN_WINDOW_STATE_CHANGED_SIGNAL_SPY_H
