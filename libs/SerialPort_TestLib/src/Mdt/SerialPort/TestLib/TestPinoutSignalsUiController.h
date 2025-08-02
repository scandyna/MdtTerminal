// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_PINOUT_SIGNALS_UI_CONTROLLER_H
#define MDT_SERIAL_PORT_TEST_LIB_TEST_PINOUT_SIGNALS_UI_CONTROLLER_H

#include "Mdt/SerialPort/AbstractPinoutSignalsUiController.h"
#include "mdt_serialport_testlib_export.h"

namespace Mdt{ namespace SerialPort{ namespace TestLib{

  class MDT_SERIALPORT_TESTLIB_EXPORT TestPinoutSignalsUiController : public AbstractPinoutSignalsUiController
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    TestPinoutSignalsUiController(QObject *parent = nullptr);

    void setTimerTimeoutEvent();

    // bool deduceReceiveDataState() const noexcept;
    // bool shouldNotifyReceiveDataChanged() const noexcept;

    bool timerIsActive() const override;

   private:

    void startTimer() override;
    void stopTimer() override;

    bool mTimerIsActive = false;
  };

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{

#endif // #ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_PINOUT_SIGNALS_UI_CONTROLLER_H
