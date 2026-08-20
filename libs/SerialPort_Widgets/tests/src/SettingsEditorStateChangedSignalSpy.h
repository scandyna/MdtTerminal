// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef SETTINGS_EDITOR_STATE_CHANGED_SIGNAL_SPY_H
#define SETTINGS_EDITOR_STATE_CHANGED_SIGNAL_SPY_H

#include "Mdt/SerialPort/SettingsEditorState.h"
#include "Mdt/SerialPort/SettingsEditorStateMachine.h"
#include "mdt_serialport_testlib_export.h"
#include <QObject>
#include <vector>
#include <cassert>


/*! \brief Helper class to test SettingsEditorStateMachine::currentStateChanged() emission
 */
class SettingsEditorStateChangedSignalSpy : public QObject
{
  Q_OBJECT

  public:

  using StateEnum = Mdt::SerialPort::SettingsEditorState::StateEnum;

  explicit
  SettingsEditorStateChangedSignalSpy(Mdt::SerialPort::SettingsEditorStateMachine *sm, QObject *parent = nullptr);

  /*! \brief Get the count of signals this spy has collected
   */
  size_t count() const noexcept
  {
    return mStateList.size();
  }

  /*! \brief Get the state at given index
   *
   * \pre \a index must be in range
   */
  StateEnum enumStateAt(size_t index) const noexcept
  {
    assert( index < count() );

    return mStateList[index];
  }

  /*! \brief Clear this spy
   */
  void clear() noexcept;

 private Q_SLOTS:

  void appendStateChanged(const Mdt::SerialPort::SettingsEditorState & state);

 private:

  std::vector<StateEnum> mStateList;
};

#endif // #ifndef SETTINGS_EDITOR_STATE_CHANGED_SIGNAL_SPY_H
