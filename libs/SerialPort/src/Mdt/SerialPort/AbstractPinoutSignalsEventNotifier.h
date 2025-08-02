// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_ABSTRACT_PINOUT_SIGNALS_EVENT_NOTIFIER_H
#define MDT_SERIAL_PORT_ABSTRACT_PINOUT_SIGNALS_EVENT_NOTIFIER_H

#include "Mdt/SerialPort/PinoutSignals.h"
#include "mdt_serialport_export.h"
#include <QObject>

namespace Mdt{ namespace SerialPort{

  /*! \brief Base to implement PinoutSignalsEventNotifier
   *
   * \sa PinoutSignalsEventNotifier
   */
  class MDT_SERIALPORT_EXPORT AbstractPinoutSignalsEventNotifier : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    AbstractPinoutSignalsEventNotifier(QObject *parent = nullptr);

    /*! \brief Tell this notifier that the serial port has been open
     *
     * While the notifier can use the aboutToClose signal from QSerialPort,
     * no such signal exists to know that the port has been open.
     * This is why this method should be used once the serial port has been open.
     */
    void setPortOpen();

    /*! \brief Get the state of the current signals
     */
    PinoutSignals currentSignals() const noexcept
    {
      return mCurrentPinoutSignals;
    }

   Q_SIGNALS:

    /*! \brief Emitted everytime at least 1 signal changed
     */
    void signalsChanged(const PinoutSignals & ps) const;

   protected Q_SLOTS:

    /*! \brief Set aboutToClose event
     */
    void setAboutToCloseEvent();

    /*! \brief Set the timer timeout event
     */
    void setTimerTimeoutEvent();

    /*! \brief Set the readyRead event
     */
    void setReadyReadEvent();

   protected:

    /*! \internal
     */
    bool shouldNotifySignalsChanged() const noexcept;

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

    /*! \brief Get the number of bytes that are available for reading
     */
    virtual
    qint64 bytesAvailable() const = 0;

    PinoutSignals mPreviousPinoutSignals;
    PinoutSignals mCurrentPinoutSignals;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ABSTRACT_PINOUT_SIGNALS_EVENT_NOTIFIER_H
