// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_EDITOR_STATE_H
#define MDT_SERIAL_PORT_SETTINGS_EDITOR_STATE_H

#include "mdt_serialport_export.h"

namespace Mdt{ namespace SerialPort{

  /*! \brief State for settings editor
   *
   * \sa SettingsEditorStateMachine
   */
  class MDT_SERIALPORT_EXPORT SettingsEditorState
  {
   public:

    /*! \internal
     */
    enum class StateEnum
    {
      Incomplete,
      Complete,
      FetchingSystemInfo
    };

    /*! \internal
     */
    constexpr
    StateEnum enumState() const noexcept
    {
      return mEnumState;
    }

    /*! \brief Check if build settings is allowed in this state
     */
    constexpr
    bool canBuildSettings() const noexcept
    {
      return mEnumState == StateEnum::Complete;
    }

    /*! \brief Check if fetch available ports is allowed in this state
     */
    constexpr
    bool canFetchAvailablePorts() const noexcept
    {
      return mEnumState != StateEnum::FetchingSystemInfo;
    }

    /*! \brief Make a Incomplete state
     */
    static
    constexpr
    SettingsEditorState incomplete() noexcept
    {
      return SettingsEditorState(StateEnum::Incomplete);
    }

    /*! \brief Make a Complete state
     */
    static
    constexpr
    SettingsEditorState complete() noexcept
    {
      return SettingsEditorState(StateEnum::Complete);
    }

    /*! \brief Make a FetchingSystemInfo state
     */
    static
    constexpr
    SettingsEditorState fetchingSystemInfo() noexcept
    {
      return SettingsEditorState(StateEnum::FetchingSystemInfo);
    }

  private:

    constexpr
    SettingsEditorState(StateEnum s) noexcept
     : mEnumState(s)
    {
    }

    StateEnum mEnumState;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_EDITOR_STATE_H
