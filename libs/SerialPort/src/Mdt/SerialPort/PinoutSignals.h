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
#include <QSerialPort>

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

    /*! \brief Check if RX (Receive Data) signal is ON
     */
    constexpr
    bool receiveDataIsOn() const noexcept
    {
      return mRX;
    }

    /*! \brief Set TX (Transmit Data) ON or OFF
     */
    constexpr
    void setTransmitDataOn(bool on) noexcept
    {
      mTX = on;
    }

    /*! \brief Check if TX (Transmit Data) is ON
     */
    constexpr
    bool transmitDataIsOn() const noexcept
    {
      return mTX;
    }

    /*! \brief Set the pinout signals
     */
    constexpr
    void setSignals(QSerialPort::PinoutSignals ps) noexcept
    {
      mPinoutSignals = ps;
    }

    /*! \brief Set DTR (Data Terminal Ready) ON or OFF
     */
    constexpr
    void setDataTerminalReadyOn(bool on) noexcept
    {
      mPinoutSignals.setFlag(QSerialPort::DataTerminalReadySignal, on);
    }

    /*! \brief Check if DTR (Data Terminal Ready) is ON
     */
    constexpr
    bool dataTerminalReadyIsOn() const noexcept
    {
      return mPinoutSignals.testFlag(QSerialPort::DataTerminalReadySignal);
    }

    /*! \brief Set RTS (Request To Send) ON or OFF
     */
    constexpr
    void setRequestToSendOn(bool on) noexcept
    {
      mPinoutSignals.setFlag(QSerialPort::RequestToSendSignal, on);
    }

    /*! \brief Check if RTS (Request To Send) is ON
     */
    constexpr
    bool requestToSendIsOn() const noexcept
    {
      return mPinoutSignals.testFlag(QSerialPort::RequestToSendSignal);
    }

    /*! \brief Check if DCD (Data Carrier Detect) is ON
     */
    constexpr
    bool dataCarrierDetectIsOn() const noexcept
    {
      return mPinoutSignals.testFlag(QSerialPort::DataCarrierDetectSignal);
    }

    /*! \brief Clear this signals
     *
     * Will set all signals to OFF
     */
    constexpr
    void clear() noexcept
    {
      mRX = false;
      mTX = false;
      mPinoutSignals = QSerialPort::NoSignal;
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
      if(a.mTX != b.mTX){
        return false;
      }
      if(a.mPinoutSignals != b.mPinoutSignals){
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
    bool mTX = false;
    QSerialPort::PinoutSignals mPinoutSignals = QSerialPort::NoSignal;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNALS_H
