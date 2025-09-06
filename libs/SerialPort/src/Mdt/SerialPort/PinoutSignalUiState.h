// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_H
#define MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_H

#include "Mdt/SerialPort/PinoutSignalUiStateTimer.h"
#include "Mdt/SerialPort/PinoutSignalUiStateStateMachine.h"
#include "mdt_serialport_export.h"

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper class to hold a single pinout signal for the UI
   *
   * Notify the UI to often has no sense, is a waste of resources,
   * and could also crash the application (f.ex. event queue overflow).
   *
   * If a signal is only ON for some milliseconds,
   * it will not be visible on the UI.
   * We have to display it ON for some time.
   *
   * This helper has methods that can be called often,
   * but will tell if the UI state should be changed at given time.
   *
   * It will also cares about holding the ON or OFF state for some minimal amount of time.
   *
   * Here is a timing diagram that shows a scenario:
   *
   * \startuml "Pinout signal UI state - RX example"
   * !include TimingDiagrams/PinoutSignalUiStateRxExample.puml
   * \enduml
   *
   * This class uses PinoutSignalUiStateStateMachine as implementation.
   *
   * Also, under the hood, no real timer is used,
   * but only a thin wrapper arount std::chrono .
   *
   * This alows to reduce system calls when having multiple states
   * (and can also be tested in a more robust way).
   *
   * \sa PinoutSignalsUiController
   * \sa PinoutSignalUiStateStateMachine
   * \sa PinoutSignalUiStateTimer
   */
  class MDT_SERIALPORT_EXPORT PinoutSignalUiState
  {
   public:

    /*! \brief Set the hold ON duration
     */
    constexpr
    void setHoldOnDuration(std::chrono::milliseconds d) noexcept
    {
      mStateMachine.setHoldOnDuration(d);
    }

    /*! \brief Set the hold OFF duration
     */
    constexpr
    void setHoldOffDuration(std::chrono::milliseconds d) noexcept
    {
      mStateMachine.setHoldOffDuration(d);
    }

    /*! \brief Set the signal ON or OFF
     *
     * This method can be called often.
     */
    constexpr
    void setSignalOn(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      mStateMachine.setSignalOn(on, now);
    }

    /*! \brief Set the state to OFF now
     *
     * Will set this state to OFF immediatly,
     * independently from the current state (bypasses hold states).
     * Can typically be called when the port closes.
     */
    constexpr
    void setStateOffNow() noexcept
    {
      mStateMachine.setStateOffNow();
    }

    /*! \brief Set the watchdog timeout event
     */
    constexpr
    void setWatchdogTimeoutEvent(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      mStateMachine.setWatchdogTimeoutEvent(now);
    }

    /*! \brief Returns true if current state is a hold state
     */
    constexpr
    bool watchdogTimerShouldBeActive() const noexcept
    {
      return mStateMachine.watchdogTimerShouldBeActive();
    }

    /*! \brief Check if the state has changed
     */
    constexpr
    bool stateHasChanged() const noexcept
    {
      return mStateMachine.uiOnOffStateHasChanged();
    }

    /*! \brief Check if the state is ON
     *
     * The returned value has only sense just after a call of updateState().
     */
    constexpr
    bool stateIsOn() const noexcept
    {
      return mStateMachine.uiStateIsOn();
    }

   private:

    PinoutSignalUiStateStateMachine mStateMachine;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_H
