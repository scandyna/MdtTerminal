// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_ABSTRACT_PINOUT_SIGNALS_UI_CONTROLLER_H
#define MDT_SERIAL_PORT_ABSTRACT_PINOUT_SIGNALS_UI_CONTROLLER_H

#include "Mdt/SerialPort/PinoutSignals.h"
#include "Mdt/SerialPort/PinoutSignalUiState.h"
#include "Mdt/SerialPort/PinoutSignalUiStateTimer.h"
#include "mdt_serialport_export.h"
#include <QObject>
#include <chrono>

namespace Mdt{ namespace SerialPort{

  /*! \brief Base to implement PinoutSignalsUiController
   *
   * \sa PinoutSignalsUiController
   */
  class MDT_SERIALPORT_EXPORT AbstractPinoutSignalsUiController : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    AbstractPinoutSignalsUiController(QObject *parent = nullptr);

    /*! \brief Set the hold ON duration
     */
    void setHoldOnDuration(std::chrono::milliseconds d) noexcept;

    /*! \brief Set the hold OFF duration
     */
    void setHoldOffDuration(std::chrono::milliseconds d) noexcept;

   public Q_SLOTS:

    /*! \brief Set aboutToClose event
     */
    void setAboutToCloseEvent();

    /*! \brief Set the pinous signals
     */
    void setSignals(const PinoutSignals & ps);

   Q_SIGNALS:

    /*! \brief Emitted every time the RX (Receive Data) state changed
     */
    void receiveDataChanged(bool on) const;

    /*! \brief Emitted every time the TX (Transmit Data) state changed
     */
    void transmitDataChanged(bool on) const;

    /*! \brief Emitted every time the RTS (Request To Send) state changed
     */
    void requestToSendChanged(bool on) const;

    /*! \brief Emitted every time the CTS (Clear To Send) state changed
     */
    void clearToSendChanged(bool on) const;

    /*! \brief Emitted every time the DCD (Data Carrier Detect) state changed
     */
    void dataCarrierDetectChanged(bool on) const;

    /*! \brief Emitted every time the DSR (Data Set Ready) state changed
     */
    void dataSetReadyChanged(bool on) const;

    /*! \brief Emitted every time the DTR (Data Terminal Ready) state changed
     */
    void dataTerminalReadyChanged(bool on) const;

    /*! \brief Emitted every time the RNG (Ring Indicator) state changed
     */
    void ringIndicatorChanged(bool on) const;

    /*! \brief Emitted every time the break state changed
     */
    void breakChanged(bool on) const;

   protected Q_SLOTS:

    /*! \brief Set the timer timeout event
     */
    void setWatchdogTimeoutEvent();

   protected:

    using TimePoint = PinoutSignalUiStateTimer::TimePoint;

    /*! \brief Returns true if current state of any UI state is a hold state
     */
    bool watchdogTimerShouldBeActive() const noexcept;

   private:

    void notifyChangedStates();

    virtual
    TimePoint getCurrentTime() const = 0;

    void startWatchdogTimerIfRequired();

    /*! \brief Start the timer
     */
    virtual
    void startWatchdogTimer() = 0;

    /*! \brief Check the timer is active (running)
     */
    virtual
    bool watchdogTimerIsActive() const = 0;

    /*! \brief Stop the timer
     *
     * \todo rename stopWatchdogTimer()
     */
    virtual
    void stopWatchdogTimer() = 0;

    PinoutSignalUiState mReceiveDataState;
    PinoutSignalUiState mTransmitDataState;
    PinoutSignalUiState mRequestToSendState;
    PinoutSignalUiState mClearToSendState;
    PinoutSignalUiState mDataCarrierDetectState;
    PinoutSignalUiState mDataSetReadyState;
    PinoutSignalUiState mDataTerminalReadyState;
    PinoutSignalUiState mRingIndicatorState;
    PinoutSignalUiState mBreakState;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ABSTRACT_PINOUT_SIGNALS_UI_CONTROLLER_H
