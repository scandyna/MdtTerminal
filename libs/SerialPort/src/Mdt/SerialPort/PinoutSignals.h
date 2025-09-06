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

    /*! \brief Set DSR (Data Set Ready ) ON or OFF
     */
    constexpr
    void setDataSetReadyOn(bool on) noexcept
    {
      mPinoutSignals.setFlag(QSerialPort::DataSetReadySignal, on);
    }

    /*! \brief Check if DSR (Data Set Ready ) is ON
     */
    constexpr
    bool dataSetReadyIsOn() const noexcept
    {
      return mPinoutSignals.testFlag(QSerialPort::DataSetReadySignal);
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

    /*! \brief Set CTS (Clear To Send) ON or OFF
     */
    constexpr
    void setClearToSendOn(bool on) noexcept
    {
      mPinoutSignals.setFlag(QSerialPort::ClearToSendSignal, on);
    }

    /*! \brief Check if CTS (Clear To Send) is ON
     */
    constexpr
    bool clearToSendIsOn() const noexcept
    {
      return mPinoutSignals.testFlag(QSerialPort::ClearToSendSignal);
    }

    /*! \brief Set DCD (Data Carrier Detect) ON or OFF
     */
    constexpr
    void setDataCarrierDetectOn(bool on) noexcept
    {
      mPinoutSignals.setFlag(QSerialPort::DataCarrierDetectSignal, on);
    }

    /*! \brief Check if DCD (Data Carrier Detect) is ON
     */
    constexpr
    bool dataCarrierDetectIsOn() const noexcept
    {
      return mPinoutSignals.testFlag(QSerialPort::DataCarrierDetectSignal);
    }

    /*! \brief Set RI or RNG (Ring Indicator) ON or OFF  RNG
     */
    constexpr
    void setRingIndicatorOn(bool on) noexcept
    {
      mPinoutSignals.setFlag(QSerialPort::RingIndicatorSignal, on);
    }

    /*! \brief Check if RI or RNG (Ring Indicator) is ON
     */
    constexpr
    bool ringIndicatorIsOn() const noexcept
    {
      return mPinoutSignals.testFlag(QSerialPort::RingIndicatorSignal);
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
