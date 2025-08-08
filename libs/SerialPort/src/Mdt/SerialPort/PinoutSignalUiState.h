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

#include "mdt_serialport_export.h"
#include <chrono>

#include <cstddef>


namespace Mdt{ namespace SerialPort{

  /*! \brief Helper for PinoutSignalUiState
   *
   * \todo document: particularité, ne mesure pas le temp lui-même
   *
   */
  class PinoutSignalUiStateTimer
  {
   public:
    
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
    // using Duration = std::chrono::milliseconds;
    
    void start(TimePoint initialTime);
    
    /*! \brief
     *
     * \pre \a t must be >= initialTime
     */
    void setCurrentTime(TimePoint t);
    
    void setDuration(std::chrono::milliseconds d);
    
    bool hasExpired() const;
    
   private:

    TimePoint mInitialTime;
    TimePoint mCurrentTime; /// \todo what is defualt contructed time point ??
  };

  /*! \brief Helper for PinoutSignalUiState
   *
   * \todo Concept of some watchdog timer,
   * that only runs when state hold XY is active.
   */
  class PinoutSignalUiStateStateMachine
  {
   public:

    /*! \brief
     */
    void setSignalOn(bool on, PinoutSignalUiStateTimer::TimePoint now);

    /*! \brief 
     */
    void setWatchdogTimeoutEvent(PinoutSignalUiStateTimer::TimePoint now);

    /*! \brief Returns true if current state is a hold state
     */
    bool watchdogTimerShouldBeActive();
    
    bool shouldStartWatchdogTimer();

    /*! \brief
     */
    bool uiOnOffStateHasChanged() const;

    bool stateIsOn() const noexcept;
  };

  /*! \brief Helper class to hold a single pinout signal for the UI
   *
   * \sa PinoutSignalsUiController
   */
  class MDT_SERIALPORT_EXPORT PinoutSignalUiState
  {
   public:

    /*! \brief Set the signal ON or OFF
     *
     * This method can be called often.
     */
    constexpr
    void setSignalOn(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      if(on){
        ++mOnCount;
      }
    }

    /*! \brief 
     */
    void setWatchdogTimeoutEvent(PinoutSignalUiStateTimer::TimePoint now);

    /*! \brief Update the state
     *
     * This method should be called jut before stateIsOn().
     * It will calculate the state regarding given time
     * and the various calls of setSignalOn().
     */
    [[deprecated]]
    constexpr
    void updateState(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      mPreviousState = mState;
      mState = deduceNewState();
      mOnCount = 0;
    }

    /*! \brief Check if the state has changed
     *
     * The returned value has only sense just after a call of updateState().
     */
    constexpr
    bool stateHasChanged() const noexcept
    {
      return mState != mPreviousState;
    }

    /*! \brief Check if the state is ON
     *
     * The returned value has only sense just after a call of updateState().
     */
    constexpr
    bool stateIsOn() const noexcept
    {
      return mState;
    }

   private:

    constexpr
    bool deduceNewState() const noexcept
    {
      return mOnCount > 0;
    }

    size_t mOnCount = 0;
    bool mState = false;
    bool mPreviousState = false;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_H
