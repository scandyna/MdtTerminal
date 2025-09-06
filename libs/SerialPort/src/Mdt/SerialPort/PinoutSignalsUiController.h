// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PINOUT_SIGNALS_UI_CONTROLLER_H
#define MDT_SERIAL_PORT_PINOUT_SIGNALS_UI_CONTROLLER_H

#include "Mdt/SerialPort/AbstractPinoutSignalsUiController.h"
#include "mdt_serialport_export.h"
#include <QObject>
#include <QTimer>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper to notify the UI the various states of the pinout signals it has to display
   *
   * PinoutSignalsEventNotifier will try to notify as much changes as possible.
   * While this can be useful for tracing, it will not work for UI display.
   *
   * Notify the UI to often has no sense, is a waste of resources,
   * and could also crash the application (f.ex. event queue overflow).
   *
   * If a signal is only ON for some milliseconds,
   * it will not be visible on the UI.
   * We have to display it ON for some time.
   *
   * Each UI state is implemented as PinoutSignalUiState.
   *
   * \sa PinoutSignalUiState
   */
  class MDT_SERIALPORT_EXPORT PinoutSignalsUiController : public AbstractPinoutSignalsUiController
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    PinoutSignalsUiController(QObject *parent = nullptr);

   private:

    TimePoint getCurrentTime() const override;
    void startWatchdogTimer() override;
    bool watchdogTimerIsActive() const override;
    void stopWatchdogTimer() override;

    QTimer mTimer;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNALS_UI_CONTROLLER_H
