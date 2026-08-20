// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_EDITOR_STATE_MACHINE_H
#define MDT_SERIAL_PORT_SETTINGS_EDITOR_STATE_MACHINE_H

#include "Mdt/SerialPort/SettingsEditorState.h"
#include "mdt_serialport_export.h"
#include <QObject>

namespace Mdt{ namespace SerialPort{

  /*! \brief State machine for settings editor
   *
   * \startuml "Settings editor state machine"
   * !include StateDiagrams/SerialPortSettingsEditorStateMachine.puml
   * \enduml
   *
   * \sa SettingsEditor
   */
  class MDT_SERIALPORT_EXPORT SettingsEditorStateMachine : public QObject
  {
    Q_OBJECT

    using StateEnum = SettingsEditorState::StateEnum;

   public:

    /*! \brief Constructor
     */
    explicit
    SettingsEditorStateMachine(QObject *parent = nullptr);

    /*! \brief Start this state machine
     */
    void start();

    /*! \brief Set startFetchingSystemInfo event
     */
    void setStartFetchingSystemInfoEvent();

    /*! \brief Set settingsComplete event
     */
    void setSettingsCompleteEvent();

    /*! \brief Set settingsIncomplete event
     */
    void setSettingsIncompleteEvent();

    /*! \internal
     */
    SettingsEditorState::StateEnum currentEnumState() const noexcept
    {
      return mCurrentState.enumState();
    }

   Q_SIGNALS:

    /*! \brief Emitted every time current state changed
     */
    void currentStateChanged(const SettingsEditorState & state) const;

   private:

    void transitFrom_Incomplete_to_Complete();
    void transitFrom_Incomplete_to_FetchingSystemInfo();
    void transitFrom_Complete_to_Incomplete();
    void transitFrom_Complete_to_FetchingSystemInfo();
    void transitFrom_FetchingSystemInfo_to_Incomplete();
    void transitFrom_FetchingSystemInfo_to_Complete();
    void updateAndNotifyNewState(const SettingsEditorState & state);

    SettingsEditorState mCurrentState = SettingsEditorState::incomplete();
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_EDITOR_STATE_MACHINE_H
