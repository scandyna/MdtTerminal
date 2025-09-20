// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MAIN_WINDOW_STATE_H
#define MAIN_WINDOW_STATE_H

/*! \brief State for MainWindow
 *
 * \sa MainWindowStateMachine
 */
class MainWindowState
{
 public:

  /*! \brief State enumeration
   */
  enum class StateEnum
  {
    PortClosed,
    PortOpen
  };

  /*! \internal
   */
  constexpr
  StateEnum enumState() const noexcept
  {
    return mEnumState;
  }

  /*! \brief Check if configure port is allowed in this state
   */
  constexpr
  bool canConfigurePort() const noexcept
  {
    return mEnumState == StateEnum::PortClosed;
  }

  /*! \brief Check if open port is allowed in this state
   */
  constexpr
  bool canOpenPort() const noexcept
  {
    return mEnumState == StateEnum::PortClosed;
  }

  /*! \brief Check if close port is allowed in this state
   */
  constexpr
  bool canClosePort() const noexcept
  {
    return mEnumState != StateEnum::PortClosed;
  }

  /*! \brief Check if submitCommand is allowed in this state
   */
  constexpr
  bool canSubmitCommand() const noexcept
  {
    return canSendData();
  }

  /*! \brief Check if set DTR is allowed in this state
   */
  constexpr
  bool canSetDTR() const noexcept
  {
    return canSendData();
  }

  /*! \brief Check if set RTS is allowed in this state
   */
  constexpr
  bool canSetRTS() const noexcept
  {
    return canSendData();
  }

  /*! \brief Check if set break is allowed in this state
   */
  constexpr
  bool canSetBreak() const noexcept
  {
    return canSendData();
  }

  /*! \brief Check if send XON is allowed in this state
   */
  constexpr
  bool canSendXON() const noexcept
  {
    return canSendData();
  }

  /*! \brief Check if send XOFF is allowed in this state
   */
  constexpr
  bool canSendXOFF() const noexcept
  {
    return canSendData();
  }

  /*! \brief Make a PortClosed state
   */
  static
  constexpr
  MainWindowState portClosed() noexcept
  {
    return MainWindowState(StateEnum::PortClosed);
  }

  /*! \brief Make a PortOpen state
   */
  static
  constexpr
  MainWindowState portOpen() noexcept
  {
    return MainWindowState(StateEnum::PortOpen);
  }

 private:

  constexpr
  bool canSendData() const noexcept
  {
    return mEnumState == StateEnum::PortOpen;
  }

  constexpr
  MainWindowState(StateEnum s) noexcept
   : mEnumState(s)
  {
  }

  StateEnum mEnumState;
};

#endif // #ifndef MAIN_WINDOW_STATE_H
