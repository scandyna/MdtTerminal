// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PINOUT_SIGNALS_H
#define MDT_SERIAL_PORT_PINOUT_SIGNALS_H

#include "mdt_serialport_export.h"

namespace Mdt{ namespace SerialPort{

  /*! \brief Holds the states of the pinout signals
   */
  class MDT_SERIALPORT_EXPORT PinoutSignals
  {
   public:

    /*! \brief Construct default pinout signals
     */
    constexpr
    PinoutSignals() noexcept = default;

    /*! \brief Set RX (Receive Data) signal ON or OFF
     */
    constexpr
    void setReceiveDataOn(bool on) noexcept
    {
      mRX = on;
    }

    /*! \brief Check if RX (Receive Data) signal is on
     */
    constexpr
    bool receiveDataIsOn() const noexcept
    {
      return mRX;
    }

    /*! \brief Check if given signals \a a are equal to \a b
     */
    constexpr
    friend
    bool operator==(const PinoutSignals & a, const PinoutSignals & b) noexcept
    {
      if(a.mRX != b.mRX){
        return false;
      }

      return true;
    }

    /*! \brief Check if given signals \a a are not equal to \a b
     */
    constexpr
    friend
    bool operator!=(const PinoutSignals & a, const PinoutSignals & b) noexcept
    {
      return !(a == b);
    }

   private:

    bool mRX = false;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNALS_H
