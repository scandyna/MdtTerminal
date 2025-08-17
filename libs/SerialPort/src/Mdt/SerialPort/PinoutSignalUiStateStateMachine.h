// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_STATE_MACHINE_H
#define MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_STATE_MACHINE_H

#include "Mdt/SerialPort/PinoutSignalUiStateTimer.h"
#include "mdt_serialport_export.h"
#include <chrono>
#include <cassert>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper for PinoutSignalUiState
   */
  class MDT_SERIALPORT_EXPORT PinoutSignalUiStateStateMachine
  {
   public:

    /*! \internal
     */
    enum class State
    {
      UiOff,
      UiOffHold,
      UiOffHoldOnRequested,
      UiOnHold,
      UiOnHoldOffRequested,
      UiOn
    };

    /*! \brief Set the hold ON duration
     */
    constexpr
    void setHoldOnDuration(std::chrono::milliseconds d) noexcept
    {
      mHoldOnTimer.setDuration(d);
    }

    /*! \brief Set the hold OFF duration
     */
    constexpr
    void setHoldOffDuration(std::chrono::milliseconds d) noexcept
    {
      mHoldOffTimer.setDuration(d);
    }

    /*! \internal
     */
    constexpr
    State currentState() const noexcept
    {
      return mCurrentState;
    }

    /*! \brief Set the signal ON or OFF
     */
    constexpr
    void setSignalOn(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      switch(mCurrentState){
        case State::UiOff:
          handleSignalOnEvent_in_UiOff(on, now);
          break;
        case State::UiOffHold:
          handleSignalOnEvent_in_UiOffHold(on, now);
          break;
        case State::UiOffHoldOnRequested:
          handleSignalOnEvent_in_UiOffHoldOnRequested(on, now);
          break;
        case State::UiOnHold:
          handleSignalOnEvent_in_UiOnHold(on, now);
          break;
        case State::UiOnHoldOffRequested:
          handleSignalOnEvent_in_UiOnHoldOffRequested(on, now);
          break;
        case State::UiOn:
          handleSignalOnEvent_in_UiOn(on, now);
          break;
      }

//       if(on){
//         switch(mCurrentState){
//           case State::UiOff:
//             transitFrom_UiOff_to_UiOnHold(now);
//             break;
//           case State::UiOnHold:
//             mUiOnOffStateHasChanged = false;
//             break;
//         }
//       }else{
//         switch(mCurrentState){
//           case State::UiOnHold:
//             
//             break;
//         }
//       }
    }

    /*! \brief Set the watchdog timeout event
     */
    constexpr
    void setWatchdogTimeoutEvent(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      switch(mCurrentState){
        case State::UiOnHold:
          handleWatchdogTimeoutEvent_in_UiOnHold(now);
          break;
        case State::UiOnHoldOffRequested:
          handleWatchdogTimeoutEvent_in_UiOnHoldOffRequested(now);
          break;
        case State::UiOffHold:
          handleWatchdogTimeoutEvent_in_UiOffHold(now);
          break;
        case State::UiOffHoldOnRequested:
          handleWatchdogTimeoutEvent_in_UiOffHoldOnRequested(now);
          break;
      }
    }

    /*! \brief Returns true if current state is a hold state
     */
    constexpr
    bool watchdogTimerShouldBeActive() const noexcept
    {
      switch(mCurrentState){
        case State::UiOnHold:
        case State::UiOnHoldOffRequested:
        case State::UiOffHold:
        case State::UiOffHoldOnRequested:
          return true;
        case State::UiOn:
        case State::UiOff:
          break;
      }

      return false;
    }

    /*! \brief Check if the ON/OFF state has changed
     */
    constexpr
    bool uiOnOffStateHasChanged() const noexcept
    {
      return mUiOnOffStateHasChanged;
    }

    /*! \brief Check if the UI state is ON or OFF
     */
    constexpr
    bool uiStateIsOn() const noexcept
    {
      switch(mCurrentState){
        case State::UiOn:
        case State::UiOnHold:
        case State::UiOnHoldOffRequested:
          return true;
        case State::UiOff:
          break;
      }

      return false;
    }

   private:

    constexpr
    void handleSignalOnEvent_in_UiOff(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOff);

      if(on){
        transitFrom_UiOff_to_UiOnHold(now);
      }
    }

    constexpr
    void handleSignalOnEvent_in_UiOffHold(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOffHold);

      if( mHoldOffTimer.hasExpired(now) ){
        transitFrom_UiOffHold_to_UiOff(now);
        return;
      }

      if(on){
        transitFrom_UiOffHold_to_UiOffHoldOnRequested(now);
      }else{
        mUiOnOffStateHasChanged = false;
      }
    }

    constexpr
    void handleWatchdogTimeoutEvent_in_UiOffHold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOffHold);

      handleSignalOnEvent_in_UiOffHold(false, now);
    }

    constexpr
    void handleSignalOnEvent_in_UiOffHoldOnRequested(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOffHoldOnRequested);

      if( mHoldOffTimer.hasExpired(now) ){
        transitFrom_UiOffHoldOnRequested_to_UiOnHold(now);
        return;
      }

      if(!on){
        transitFrom_UiOffHoldOnRequested_to_UiOffHold(now);
      }
    }

    constexpr
    void handleWatchdogTimeoutEvent_in_UiOffHoldOnRequested(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOffHoldOnRequested);

      handleSignalOnEvent_in_UiOffHoldOnRequested(true, now);
    }

    constexpr
    void handleSignalOnEvent_in_UiOnHold(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOnHold);

      if( mHoldOnTimer.hasExpired(now) ){
        transitFrom_UiOnHold_to_UiOn(now);
        return;
      }

      if(on){
        mUiOnOffStateHasChanged = false;
      }else{
        transitFrom_UiOnHold_to_UiOnHoldOffRequested(now);
      }
    }

    constexpr
    void handleWatchdogTimeoutEvent_in_UiOnHold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOnHold);

      handleSignalOnEvent_in_UiOnHold(true, now);
    }

    constexpr
    void handleSignalOnEvent_in_UiOnHoldOffRequested(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOnHoldOffRequested);

      if( mHoldOnTimer.hasExpired(now) ){
        transitFrom_UiOnHoldOffRequested_to_UiOffHold(now);
        return;
      }

      if(on){
        transitFrom_UiOnHoldOffRequested_to_UiOnHold(now);
      }
    }

    constexpr
    void handleWatchdogTimeoutEvent_in_UiOnHoldOffRequested(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOnHoldOffRequested);

      handleSignalOnEvent_in_UiOnHoldOffRequested(false, now);
    }

    constexpr
    void handleSignalOnEvent_in_UiOn(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOn);

      if(!on){
        transitFrom_UiOn_to_UiOffHold(now);
      }
    }

    constexpr
    void transitFrom_UiOff_to_UiOnHold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOff);

      mCurrentState = State::UiOnHold;
      mUiOnOffStateHasChanged = true;
      startHoldOnTimer(now);
    }

    constexpr
    void transitFrom_UiOffHold_to_UiOffHoldOnRequested(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOffHold);

      mCurrentState = State::UiOffHoldOnRequested;
      mUiOnOffStateHasChanged = false;
    }

    constexpr
    void transitFrom_UiOffHold_to_UiOff(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOffHold);

      mCurrentState = State::UiOff;
      mUiOnOffStateHasChanged = false;
    }

    constexpr
    void transitFrom_UiOffHoldOnRequested_to_UiOffHold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOffHoldOnRequested);

      mCurrentState = State::UiOffHold;
    }

    constexpr
    void transitFrom_UiOffHoldOnRequested_to_UiOnHold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOffHoldOnRequested);

      mCurrentState = State::UiOnHold;
      mUiOnOffStateHasChanged = true;
      startHoldOnTimer(now);
    }

    constexpr
    void transitFrom_UiOnHold_to_UiOn(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOnHold);

      mCurrentState = State::UiOn;
      mUiOnOffStateHasChanged = false;
    }

    constexpr
    void transitFrom_UiOnHold_to_UiOnHoldOffRequested(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOnHold);

      mCurrentState = State::UiOnHoldOffRequested;
      mUiOnOffStateHasChanged = false;
    }

    constexpr
    void transitFrom_UiOnHoldOffRequested_to_UiOnHold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOnHoldOffRequested);

      mCurrentState = State::UiOnHold;
    }

    constexpr
    void transitFrom_UiOnHoldOffRequested_to_UiOffHold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOnHoldOffRequested);

      mCurrentState = State::UiOffHold;
      mUiOnOffStateHasChanged = true;
      startHoldOffTimer(now);
    }

    constexpr
    void transitFrom_UiOn_to_UiOffHold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOn);

      mCurrentState = State::UiOffHold;
      mUiOnOffStateHasChanged = true;
      startHoldOffTimer(now);
    }

    constexpr
    void startHoldOnTimer(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      mHoldOnTimer.start(now);
    }

    constexpr
    bool holdOnTimeout(PinoutSignalUiStateTimer::TimePoint now) const noexcept
    {
      return mHoldOnTimer.hasExpired(now);
    }

    constexpr
    void startHoldOffTimer(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      mHoldOffTimer.start(now);
    }

    constexpr
    bool holdOffTimeout(PinoutSignalUiStateTimer::TimePoint now) const noexcept
    {
      return mHoldOffTimer.hasExpired(now);
    }

    bool mUiOnOffStateHasChanged = false;
    State mCurrentState = State::UiOff;
    PinoutSignalUiStateTimer mHoldOnTimer;
    PinoutSignalUiStateTimer mHoldOffTimer;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_STATE_MACHINE_H
