// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PINOUT_SIGNALS_EVENT_NOTIFIER_H
#define MDT_SERIAL_PORT_PINOUT_SIGNALS_EVENT_NOTIFIER_H

#include "Mdt/SerialPort/AbstractPinoutSignalsEventNotifier.h"
#include "mdt_serialport_export.h"
#include <QSerialPort>
#include <QPointer>
#include <QTimer>

namespace Mdt{ namespace SerialPort{

  /*! \brief Get pinout signals states from the serial port and notify once changed
   *
   * PinoutSignalsEventNotifier can be used to capture pinout signals from a serial port.
   * Every time something changes, a notification will be emitted.
   * This could be used for tracing or mybe logging.
   *
   * The amount of notifications can be to much to be displayed on an UI.
   * To display the signals to the user, consider also PinoutSignalsUiController .
   *
   * Receive events:
   * - QSerialPort::readyRead(): new data is available for reading from the device
   * - QSerialPort::bytesWritten(): a payload of data has been written to the device
   * - QSerialPort::breakEnabledChanged(): ?
   * - QSerialPort::dataTerminalReadyChanged(): DTR
   * - QSerialPort::requestToSendChanged(): RTS
   *
   * Because some signals are not notified by QSerialPort,
   * they will be readen using QSerialPort::pinoutSignals().
   *
   * If no event has been triggered for some time interval Ti,
   * states will also be readen periodically:
   * \code
   *       timeout      To
   * timer run     -----  ---  -----
   *       reset         R    R 
   * some event              E
   *               <--->
   *                Ti
   * \endcode
   *
   *
   * \todo When a port error occurs, f.ex. an USB adapter is unplugged,
   * readPinoutSignals() will blindly continue to call mSerialPort->pinoutSignals();
   * This will produce QSerialPort to emit errorOccured() each time.
   * We should check the QSerialPort::error() before read.
   * Also, wehen a read fails, we should tell that the pinout signals is not reliable.
   * This means, we no longer directly emit PinoutSignals,
   * but some container class that also indicates if we have signals or an error.
   * Notice that this would also require PinoutSignalUiState to handle some
   * error / uncertainty state.
   * \sa https://gitlab.com/scandyna/mdtterminal/-/issues/5
   *
   * \todo How can we make TX and RX a bit reliable ?
   * bytesWritten() TX ON. TX OFF: when ?
   * readyRead() RX ON. RX OFF: when ?
   * maybe QSerialPort::bytesAvailable() and QSerialPort::bytesToWrite()
   *
   *
   * \sa PinoutSignals
   * \sa PinoutSignalsUiController
   * \sa https://doc.qt.io/qt-6/qserialport.html#pinoutSignals
   * \sa https://doc.qt.io/qt-6/qiodevice.html#readyRead
   * \sa https://doc.qt.io/qt-6/qiodevice.html#bytesWritten
   */
  class MDT_SERIALPORT_EXPORT PinoutSignalsEventNotifier : public AbstractPinoutSignalsEventNotifier
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     *
     * \pre \a serialPort must be a valid pointer
     */
    explicit
    PinoutSignalsEventNotifier(QSerialPort *serialPort, QObject *parent = nullptr);

   private:

    void startTimer() override;
    bool timerIsActive() const override;
    void stopTimer() override;

    qint64 bytesAvailable() const override;
    qint64 bytesToWrite() const override;

    QSerialPort::PinoutSignals readPinoutSignals() override;

    QPointer<QSerialPort> mSerialPort;
    QTimer mTimer;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNALS_EVENT_NOTIFIER_H
