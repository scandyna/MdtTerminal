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
#include <cstddef>

namespace Mdt{ namespace SerialPort{

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
    void setSignalOn(bool on) noexcept
    {
      if(on){
        ++mOnCount;
      }
    }

    /*! \brief Update the state
     *
     * This method should be called jut before stateIsOn().
     * It will calculate the state regarding the various
     * calls of setSignalOn().
     */
    constexpr
    void updateState() noexcept
    {
      // const bool newState = deduceNewState();
      // mStateChanged = newState != mState;
      // mState = newState;

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
