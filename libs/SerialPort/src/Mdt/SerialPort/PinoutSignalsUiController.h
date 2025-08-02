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

/// Chat proposition:
// /* In PinoutSignalsUiController.h */
// 
// #include <QObject>
// #include <QTimer>
// // … other includes
// 
// class MDT_SERIALPORT_EXPORT PinoutSignalsUiController : public QObject
// {
// Q_OBJECT
// public:
// explicit PinoutSignalsUiController(QObject *parent = nullptr);
// 
// public Q_SLOTS:
// void setSignals(const PinoutSignals &ps);
// 
// Q_SIGNALS:
// void receiveDataChanged(bool on);
// 
// private Q_SLOTS:
// void onHoldTimeout();
// private:
// bool mCurrentRX = false; // current displayed state
// QTimer mHoldTimer; // timer to enforce minimum display time
// const int mMinOnDurationMs = 100; // minimum duration in ms to show an ON signal
// };

// /* In PinoutSignalsUiController.cpp */
// 
// #include "PinoutSignalsUiController.h"
// 
// PinoutSignalsUiController::PinoutSignalsUiController(QObject *parent)
// : QObject(parent)
// {
// // Configure the hold timer (single-shot ensures it fires only once per activation)
// mHoldTimer.setSingleShot(true);
// mHoldTimer.setInterval(mMinOnDurationMs);
// connect(&mHoldTimer, &QTimer::timeout, this, &PinoutSignalsUiController::onHoldTimeout);
// }
// 
// void PinoutSignalsUiController::setSignals(const PinoutSignals &ps)
// {
// bool newRX = ps.receiveDataIsOn();
// 
// // If the signal hasn't changed, do nothing
// if(newRX == mCurrentRX)
// return;
// 
// if(newRX) {
// // When signal goes ON, update immediately and start timer.
// mCurrentRX = true;
// emit receiveDataChanged(true);
// mHoldTimer.start();
// } else {
// // When signal goes OFF: if timer is still running,
// // then ignore the OFF until the timer expires.
// if(!mHoldTimer.isActive()) {
// mCurrentRX = false;
// emit receiveDataChanged(false);
// }
// // Otherwise, do nothing. The timer callback will handle turning it off.
// }
// }
// void PinoutSignalsUiController::onHoldTimeout()
// {
// // Timer has expired – if current signal is still ON but the underlying value is now OFF,
// // then update the UI to switch OFF.
// // In a more integrated design, you might re-query the underlying state.
// // Here, we simply force OFF if no new ON event occurred.
// mCurrentRX = false;
// emit receiveDataChanged(false);
// }
// 
// How This Helps:
// • When a rapid pulse occurs (RX becomes ON briefly) the UI is updated immediately, then remains ON at least mMinOnDurationMs even if the raw signal goes back to OFF.
// • This mechanism prevents very brief pulses from disappearing too quickly, thus offering a smoother UI experience.
// • The logic avoids flooding the UI with off events while the timer is running, and the state is only changed when the timer callback occurs.
// 
// This pattern can be extended later if you need similar logic for other signals.
// 
// Let me know if you have questions on this approach or need further refinements!


// This alternative approach—sampling the RX state periodically and making a decision based on the accumulated values—can certainly work as a debouncing or smoothing mechanism. Instead of reacting immediately to each setSignals() call, you would:
// 
// • Use a periodic timer (e.g. every 100 ms) that on each timeout looks at how many “ON” versus “OFF” events were received during that period.
// • Decide on a final UI state based on a threshold or majority vote (for instance, if more than 50% of the events were “ON,” then show the UI as ON).
// • Reset the counters after updating the UI so the next period starts fresh.
// 
// Advantages of this method include:
// – Filtering out rapid, transient fluctuations because single, brief pulses won’t necessarily shift the overall count.
// – Potentially reducing UI update chatter, as you only change the state once per period based on the overall count.
// 
// Tradeoffs include:
// – Added latency (the UI may be delayed up to your timer interval, 100 ms, before updating).
// – You’ll need to tune the threshold or accumulation logic to ensure that brief yet still significant events are handled properly.
// – The algorithm gets slightly more complex since you’re storing and resetting counters, and you have to consider what to do if the count is exactly balanced or if there is no clear majority.
// 
// A sample implementation might look like this:
// 
// // In PinoutSignalsUiController.h
// 
// // Add new members for accumulating state counts
// private:
// int mOnCount = 0;
// int mOffCount = 0;
// QTimer mSamplingTimer;
// const int mSampleIntervalMs = 100;
// 
// // In PinoutSignalsUiController.cpp, in the constructor:
// PinoutSignalsUiController::PinoutSignalsUiController(QObject *parent)
// : QObject(parent)
// {
// connect(&mSamplingTimer, &QTimer::timeout, this, this{
// // Decide final state based on majority
// bool finalState = (mOnCount > mOffCount);
// // Only emit if the determined state differs from current state.
// if(finalState != mCurrentRX){
// mCurrentRX = finalState;
// emit receiveDataChanged(finalState);
// }
// // Reset counters after processing
// mOnCount = 0;
// mOffCount = 0;
// });
// mSamplingTimer.start(mSampleIntervalMs);
// }
// 
// // In setSignals(), instead of direct notification:
// void PinoutSignalsUiController::setSignals(const PinoutSignals &ps)
// {
// bool newRX = ps.receiveDataIsOn();
// // Accumulate the events for the current period
// if(newRX)
// ++mOnCount;
// else
// ++mOffCount;
// }
// 
// With this approach, each call to setSignals() only updates your counters, and the actual decision is deferred to the timer’s timeout slot, which periodically “samples” the accumulated calls. Adjusting the mSampleIntervalMs and your decision logic (for example, a weighted average or a required minimum count) gives you flexibility over responsiveness versus noise immunity.
// 
// This method is a valid alternative to the per-event hold timer approach. Its success depends on the characteristics of your input signal and the responsiveness you want in your UI.

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
   * \section Mdt_SerialPort_PinoutSignalsUiController_Rationale Rationale
   *
   *
   * \startuml "Pinout signals UI controller"
   * !include TimingDiagrams/PinoutSignalsUiController.puml
   * \enduml
   *
   * \todo every time RX UI changes, notify
   *
   * \code
   * bool deduceRxState() const
   * {
   *   return RxOnCount > RxOffCount;
   * }
   * \endcode
   *
   * \code
   * const bool newRxUi = deduceRxState();
   * if(newRxUi != RxUi){
   *   notify(newRX);
   *   RxUi = newRX;
   * }
   * \endcode
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
   *
   * \section Mdt_SerialPort_PinoutSignalsUiController_Garbage Stuff to remove
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
   * \code
   * RX ON signal:   -     -  -
   * RX ON UI:       ----  --------
   *                 <-->
   *                  t?
   * \endcode
   *
   * setSignals() will be called often.
   *
   * - setSignals() - changed
   *  - 
   *
   * \todo Should also have some fake timer !
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
