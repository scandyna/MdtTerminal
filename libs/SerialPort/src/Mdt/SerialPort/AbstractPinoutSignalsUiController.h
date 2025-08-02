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
#include "mdt_serialport_export.h"
#include <QObject>
#include <cstddef>

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

   protected Q_SLOTS:

    /*! \brief Set the timer timeout event
     */
    void setTimerTimeoutEvent();

   protected:

    /*! \internal
     */
    // bool deduceReceiveDataState() const noexcept;

    /*! \internal
     */
    // bool shouldNotifyReceiveDataChanged() const noexcept;

   private:

    /*! \brief Start the timer
     */
    virtual
    void startTimer() = 0;

    /*! \brief Check the timer is active (running)
     */
    virtual
    bool timerIsActive() const = 0;

    /*! \brief Stop the timer
     */
    virtual
    void stopTimer() = 0;

    PinoutSignalUiState mReceiveDataState;
    // size_t mRxOnCount = 0;
    // bool mPreviousUiRx = false;
    // bool mCurrentUiRx = false;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ABSTRACT_PINOUT_SIGNALS_UI_CONTROLLER_H
