// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MAIN_WINDOW_STATE_MACHINE_H
#define MAIN_WINDOW_STATE_MACHINE_H

#include "MainWindowState.h"
#include <QObject>

/*! \brief State machine for MainWindow
 *
 * \startuml "MainWindow state machine"
 * !include StateDiagrams/TerminalGuiAppMainWindowStateMachine.puml
 * \enduml
 */
class MainWindowStateMachine : public QObject
{
  Q_OBJECT

  using StateEnum = MainWindowState::StateEnum;

 public:

  /*! \brief Constructor
   */
  explicit
  MainWindowStateMachine(QObject *parent = nullptr);

  /*! \brief Start this state machine
   */
  void start();

  /*! \brief Set portOpen event
   */
  void setPortOpenEvent();

  /*! \brief Set portClosed event
   */
  void setPortClosedEvent();

 signals:

  /*! \brief Emitted every time current state changed
   */
  void currentStateChanged(const MainWindowState & state) const;

 protected:

  /*! \internal
   */
  MainWindowState::StateEnum currentEnumState() const noexcept
  {
    return mCurrentState.enumState();
  }

 private:

  /*! \internal
   */
  // bool shouldNotifyCurrentStateChanged() const noexcept
  // {
  //   return mShouldNotifyCurrentStateChanged;
  // }

  void notifyCurrentStateChangedIfShould();

  void transitFrom_PortClosed_to_PortOpen();

  void transitFrom_PortOpen_to_PortClosed();

  MainWindowState mCurrentState = MainWindowState::portClosed();
  // bool mShouldNotifyCurrentStateChanged = false;
};

#endif // #ifndef MAIN_WINDOW_STATE_MACHINE_H
