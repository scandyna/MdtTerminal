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


// #include <cstddef>


namespace Mdt{ namespace SerialPort{

  /*! \brief Helper class to hold a single pinout signal for the UI
   *
   * \sa PinoutSignalsUiController
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

      // if(on){
      //   ++mOnCount;
      // }
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

    /*! \brief Update the state
     *
     * This method should be called jut before stateIsOn().
     * It will calculate the state regarding given time
     * and the various calls of setSignalOn().
     */
    // [[deprecated]]
    // constexpr
    // void updateState(PinoutSignalUiStateTimer::TimePoint now) noexcept
    // {
    //   mPreviousState = mState;
    //   mState = deduceNewState();
    //   mOnCount = 0;
    // }

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
      // return mState;
    }

   private:

    // constexpr
    // bool deduceNewState() const noexcept
    // {
    //   return mOnCount > 0;
    // }

    PinoutSignalUiStateStateMachine mStateMachine;
    
    // size_t mOnCount = 0;
    // bool mState = false;
    // bool mPreviousState = false;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_H
