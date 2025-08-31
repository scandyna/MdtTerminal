// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_PINOUT_SIGNALS_EVENT_NOTIFIER_H
#define MDT_SERIAL_PORT_TEST_LIB_TEST_PINOUT_SIGNALS_EVENT_NOTIFIER_H

#include "Mdt/SerialPort/AbstractPinoutSignalsEventNotifier.h"
#include "mdt_serialport_testlib_export.h"

namespace Mdt{ namespace SerialPort{ namespace TestLib{

  /*! \brief
   */
  class MDT_SERIALPORT_TESTLIB_EXPORT TestPinoutSignalsEventNotifier : public AbstractPinoutSignalsEventNotifier
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    TestPinoutSignalsEventNotifier(QObject *parent = nullptr);

    void setAboutToCloseEvent();
    void setTimerTimeoutEvent();
    void setReadyReadEvent();
    void setBytesWrittenEvent(qint64 bytes);
    void setDataTerminalReadyChangedEvent(bool set);
    void setBytesAvailable(qint64 count);
    void setBytesToWrite(qint64 count);
    void setPortPinoutSignals(QSerialPort::PinoutSignals ps);

    bool shouldNotifySignalsChanged() const noexcept;

    void updateReceiveDataState();
    void readAndUpdatePinoutSignalsStates();

    bool timerIsActive() const override;
    bool timerHasBeenReset() const;

   private:

    void startTimer() override;
    void stopTimer() override;

    qint64 bytesAvailable() const override;
    qint64 bytesToWrite() const override;

    QSerialPort::PinoutSignals readPinoutSignals() override;

    qint64 mBytesAvailable = 0;
    qint64 mBytesToWrite = 0;

    bool mTimerIsActive = false;
    QSerialPort::PinoutSignals mPortPinoutSignals = QSerialPort::NoSignal;
  };

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{

#endif // #ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_PINOUT_SIGNALS_EVENT_NOTIFIER_H
