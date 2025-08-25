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

    /*! \internal
     */
    constexpr
    bool currentStateIs_on_hold() const noexcept
    {
      switch(mCurrentState){
        case State::UiOnHold:
        case State::UiOnHoldOffRequested:
          return true;
        default:
          break;
      }

      return false;
    }

    /*! \internal
     */
    constexpr
    bool currentStateIs_off_hold() const noexcept
    {
      switch(mCurrentState){
        case State::UiOffHold:
        case State::UiOffHoldOnRequested:
          return true;
        default:
          break;
      }

      return false;
    }

    /*! \internal
     */
    constexpr
    void enter_on_hold_state(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert( !currentStateIs_on_hold() );

      mCurrentState = State::UiOnHold;
      startHoldOnTimer(now);
    }

    /*! \internal
     */
    constexpr
    void enter_off_hold_state(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert( !currentStateIs_off_hold() );

      mCurrentState = State::UiOffHold;
      startHoldOffTimer(now);
    }

    /*! \internal
     */
    constexpr
    PinoutSignalUiStateTimer::TimePoint holdOnTimerStartTime() const noexcept
    {
      return mHoldOnTimer.startTime();
    }

    /*! \internal
     */
    constexpr
    PinoutSignalUiStateTimer::TimePoint holdOffTimerStartTime() const noexcept
    {
      return mHoldOffTimer.startTime();
    }

    /*! \brief Set the signal ON or OFF
     */
    constexpr
    void setSignalOn(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      if( currentStateIs_on_hold() ){
        handleSignalOnEvent_in_on_hold(on, now);
        return;
      }

      if( currentStateIs_off_hold() ){
        handleSignalOnEvent_in_off_hold(on, now);
        return;
      }

      switch(mCurrentState){
        case State::UiOff:
          handleSignalOnEvent_in_UiOff(on, now);
          break;
        case State::UiOn:
          handleSignalOnEvent_in_UiOn(on, now);
          break;
        case State::UiOffHold:
        case State::UiOffHoldOnRequested:
        case State::UiOnHold:
        case State::UiOnHoldOffRequested:
          assert(false);
          break;
      }
    }

    /*! \brief Set the watchdog timeout event
     */
    constexpr
    void setWatchdogTimeoutEvent(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      if( currentStateIs_on_hold() ){
        handleWatchdogTimeoutEvent_in_on_hold(now);
        return;
      }

      if( currentStateIs_off_hold() ){
        handleWatchdogTimeoutEvent_in_off_hold(now);
        return;
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
        case State::UiOffHold:
        case State::UiOffHoldOnRequested:
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
        transitFrom_UiOff_to_on_hold(now);
      }
    }

    constexpr
    void handleSignalOnEvent_in_off_hold(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert( currentStateIs_off_hold() );

      if( mHoldOffTimer.hasExpired(now) ){
        if(on){
          transitFrom_off_hold_to_on_hold(now);
        }else{
          transitFrom_off_hold_to_UiOff();
        }
        return;
      }
      assert( !mHoldOffTimer.hasExpired(now) );

      switch(mCurrentState){
        case State::UiOffHold:
          handleSignalOnEvent_in_UiOffHold_beforeHoldOnTimeout(on);
          break;
        case State::UiOffHoldOnRequested:
          handleSignalOnEvent_in_UiOffHoldOnRequested_beforeHoldOnTimeout(on);
          break;
        default:
          assert(false);
          break;
      }
    }

    constexpr
    void handleWatchdogTimeoutEvent_in_off_hold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert( currentStateIs_off_hold() );

      if( !mHoldOffTimer.hasExpired(now) ){
        mUiOnOffStateHasChanged = false;
        return;
      }

      switch(mCurrentState){
        case State::UiOffHold:
          transitFrom_UiOffHold_to_UiOff();
          break;
        case State::UiOffHoldOnRequested:
          transitFrom_UiOffHoldOnRequested_to_on_hold(now);
          break;
        default:
          assert(false);
          break;
      }
    }

    constexpr
    void handleSignalOnEvent_in_UiOffHold_beforeHoldOnTimeout(bool on) noexcept
    {
      assert(mCurrentState == State::UiOffHold);

      if(on){
        transitFrom_UiOffHold_to_UiOffHoldOnRequested();
      }else{
        mUiOnOffStateHasChanged = false;
      }
    }

    constexpr
    void handleSignalOnEvent_in_UiOffHoldOnRequested_beforeHoldOnTimeout(bool on) noexcept
    {
      assert(mCurrentState == State::UiOffHoldOnRequested);

      if(!on){
        transitFrom_UiOffHoldOnRequested_to_UiOffHold();
      }
    }

    constexpr
    void handleSignalOnEvent_in_on_hold(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert( currentStateIs_on_hold() );

      if( mHoldOnTimer.hasExpired(now) ){
        if(on){
          transitFrom_on_hold_to_UiOn();
        }else{
          transitFrom_on_hold_to_off_hold(now);
        }
        return;
      }
      assert( !mHoldOnTimer.hasExpired(now) );

      switch(mCurrentState){
        case State::UiOnHold:
          handleSignalOnEvent_in_UiOnHold_beforeHoldOnTimeout(on);
          break;
        case State::UiOnHoldOffRequested:
          handleSignalOnEvent_in_UiOnHoldOffRequested_beforeHoldOnTimeout(on);
          break;
        default:
          assert(false);
          break;
      }
    }

    constexpr
    void handleWatchdogTimeoutEvent_in_on_hold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert( currentStateIs_on_hold() );

      if( !mHoldOnTimer.hasExpired(now) ){
        mUiOnOffStateHasChanged = false;
        return;
      }

      switch(mCurrentState){
        case State::UiOnHold:
          transitFrom_UiOnHold_to_UiOn();
          break;
        case State::UiOnHoldOffRequested:
          transitFrom_UiOnHoldOffRequested_to_off_hold(now);
          break;
        default:
          assert(false);
          break;
      }
    }

    constexpr
    void handleSignalOnEvent_in_UiOnHold_beforeHoldOnTimeout(bool on) noexcept
    {
      assert(mCurrentState == State::UiOnHold);

      if(on){
        mUiOnOffStateHasChanged = false;
      }else{
        transitFrom_UiOnHold_to_UiOnHoldOffRequested();
      }
    }

    constexpr
    void handleSignalOnEvent_in_UiOnHoldOffRequested_beforeHoldOnTimeout(bool on) noexcept
    {
      assert(mCurrentState == State::UiOnHoldOffRequested);

      if(on){
        transitFrom_UiOnHoldOffRequested_to_UiOnHold();
      }
    }

    constexpr
    void handleSignalOnEvent_in_UiOn(bool on, PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOn);

      if(!on){
        transitFrom_UiOn_to_off_hold(now);
      }
    }

    constexpr
    void transitFrom_UiOff_to_on_hold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOff);

      enter_on_hold_state(now);
      mUiOnOffStateHasChanged = true;
    }

    constexpr
    void transitFrom_UiOffHold_to_UiOffHoldOnRequested() noexcept
    {
      assert(mCurrentState == State::UiOffHold);

      mCurrentState = State::UiOffHoldOnRequested;
      mUiOnOffStateHasChanged = false;
    }

    constexpr
    void transitFrom_off_hold_to_UiOff() noexcept
    {
      assert( currentStateIs_off_hold() );

      mCurrentState = State::UiOff;
      mUiOnOffStateHasChanged = false;
    }

    constexpr
    void transitFrom_UiOffHold_to_UiOff() noexcept
    {
      assert(mCurrentState == State::UiOffHold);

      mCurrentState = State::UiOff;
      mUiOnOffStateHasChanged = false;
    }

    constexpr
    void transitFrom_UiOffHoldOnRequested_to_on_hold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOffHoldOnRequested);

      enter_on_hold_state(now);
      mUiOnOffStateHasChanged = true;
    }

    constexpr
    void transitFrom_off_hold_to_on_hold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert( currentStateIs_off_hold() );

      enter_on_hold_state(now);
      mUiOnOffStateHasChanged = true;
    }

    constexpr
    void transitFrom_UiOffHoldOnRequested_to_UiOffHold() noexcept
    {
      assert(mCurrentState == State::UiOffHoldOnRequested);

      mCurrentState = State::UiOffHold;
    }

    constexpr
    void transitFrom_on_hold_to_UiOn() noexcept
    {
      assert( currentStateIs_on_hold() );

      mCurrentState = State::UiOn;
      mUiOnOffStateHasChanged = false;
    }

    constexpr
    void transitFrom_on_hold_to_off_hold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert( currentStateIs_on_hold() );

      enter_off_hold_state(now);
      mUiOnOffStateHasChanged = true;
    }

    constexpr
    void transitFrom_UiOnHold_to_UiOn() noexcept
    {
      assert(mCurrentState == State::UiOnHold);

      mCurrentState = State::UiOn;
      mUiOnOffStateHasChanged = false;
    }

    constexpr
    void transitFrom_UiOnHold_to_UiOnHoldOffRequested() noexcept
    {
      assert(mCurrentState == State::UiOnHold);

      mCurrentState = State::UiOnHoldOffRequested;
      mUiOnOffStateHasChanged = false;
    }

    constexpr
    void transitFrom_UiOnHoldOffRequested_to_UiOnHold() noexcept
    {
      assert(mCurrentState == State::UiOnHoldOffRequested);

      mCurrentState = State::UiOnHold;
    }

    constexpr
    void transitFrom_UiOnHoldOffRequested_to_off_hold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOnHoldOffRequested);

      enter_off_hold_state(now);
      mUiOnOffStateHasChanged = true;
    }

    constexpr
    void transitFrom_UiOn_to_off_hold(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOn);

      enter_off_hold_state(now);
      mUiOnOffStateHasChanged = true;
    }

    constexpr
    void startHoldOnTimer(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      mHoldOnTimer.start(now);
    }

    constexpr
    bool holdOnTimeout(PinoutSignalUiStateTimer::TimePoint now) const noexcept
    {
      assert(mCurrentState == State::UiOnHold);

      return mHoldOnTimer.hasExpired(now);
    }

    constexpr
    void startHoldOffTimer(PinoutSignalUiStateTimer::TimePoint now) noexcept
    {
      assert(mCurrentState == State::UiOffHold);

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
