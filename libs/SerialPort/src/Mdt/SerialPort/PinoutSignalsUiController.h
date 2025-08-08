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
   *
   * - on pulse to ON, hold for 100ms (each state calculates its own duration)
   * - x
   * - setSignals() is a trigger to update UI states
   * - setSignals() gets current time and pass it to UI states
   * - at end of setSignals(), a timer is started. It will update the UI states in case no setSignals() has been called for a while
   * - UI state is ON and new signal is OFF:
   * - a) UI ON duration < holdOnDuration: UI state stays ON
   * - b) else: UI state goes OFF
   * - UI state is OFF and new signal is ON:
   * - a) UI OFF duration < holdOffDuration: UI state stays OFF AND memorises an ON request
   * - b) else: UI state goes ON
   *
   *
   * |Previous UI state|UI ON dur < holdOnDur|signal|UI state|Notes           |
   * |:---------------:|:-------------------:|:----:|:------:|:---------------|
   * |  OFF            |   false             | OFF  |  OFF   |Do nothing      |
   * |  OFF            |   false             | ON   |  ON    |Ignore UI ON dur|
   * |  OFF            |   true              | OFF  |  OFF   |Do nothing      |
   * |  OFF            |   true              | ON   |  ON    |                |
   * |  ON             |   false             | OFF  |  OFF   |                |
   * |  ON             |   false             | ON   |  ON    |Do nothing      |
   * |  ON             |   true              | OFF  |  ON    |                |
   * |  ON             |   true              | ON   |  ON    |Do nothing      |
   *
   *
   * \todo Remove entry/ startXXtimer() in states ! Put ir in transitions ! Will reduce states.
   *
   * \startuml "Pinout signals UI controller"
   * !include StateDiagrams/PinoutSignalsUiController.puml
   * \enduml
   *
   * \section Mdt_SerialPort_PinoutSignalsUiController_Rationale Rationale
   *
   * - short ON pulse
   * - long ON
   *
   * \startuml "Pinout signals UI controller"
   * !include TimingDiagrams/PinoutSignalsUiController.puml
   * \enduml
   *
   *
   * \startuml "Pinout signals UI controller - RX example of second approach"
   * !include TimingDiagrams/PinoutSignalsUiControllerRxExampleV02.puml
   * \enduml
   *
   * \subsection Mdt_SerialPort_PinoutSignalsUiController_Rationale_FirstApproach First approach
   *
   * A first approach was to have a hold ON timer.
   * When some signal, like RX, goes ON,
   * the state is memorised, the UI is notified and the timer started.
   * On timeout, if RX is OFF, we memorise and notify the UI.
   *
   * \startuml "Pinout signals UI controller - RX example of first approach"
   * !include TimingDiagrams/PinoutSignalsUiControllerRxExampleV01.puml
   * \enduml
   *
   * As the diagram shows, when RX goes ON again just after a timeout,
   * the UI will be notified again.
   * This should also be handled.
   *
   * The logic of the code seemed to complex.
   * Also, this approach would probably require 1 timer per signal.
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

    void startTimer() override;
    bool timerIsActive() const override;
    void stopTimer() override;

    QTimer mTimer;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNALS_UI_CONTROLLER_H
