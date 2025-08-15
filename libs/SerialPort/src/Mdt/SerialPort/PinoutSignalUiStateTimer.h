// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_TIMER_H
#define MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_TIMER_H

#include "mdt_serialport_export.h"
#include <chrono>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper for PinoutSignalUiState
   *
   * Thin wrapper around std::chrono.
   *
   * \code
   * using TimePoint = PinoutSignalUiStateTimer::TimePoint;
   *
   * PinoutSignalUiStateTimer timer1;
   * PinoutSignalUiStateTimer timer2;
   *
   * timer1.setDuration(100ms);
   * timer2.setDuration(60ms);
   *
   * TimePoint now = PinoutSignalUiStateTimer::now();
   *
   * timer1.start(now);
   * timer2.start(now);
   *
   * processSomeEvents();
   *
   * now = PinoutSignalUiStateTimer::now();
   *
   * if( timer1.hasExpired(now) ){
   *   doStuff1();
   *   // timer1 still used now
   *   timer1.start(now);
   * }
   * if( timer2.hasExpired(now) ){
   *   doStuff2();
   *   // timer2 not used for now ( we not call hasExpired() ) - will be started later
   * }
   * \endcode
   *
   * \todo document: particularité, ne mesure pas le temp lui-même
   *
   * \todo isActive() ?
   *
   */
  class MDT_SERIALPORT_EXPORT PinoutSignalUiStateTimer
  {
   public:

    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
    // using Duration = std::chrono::milliseconds;

    /*! \brief Set the duration until expiration
     */
    constexpr
    void setDuration(std::chrono::milliseconds d) noexcept
    {
      mDuration = d;
    }

    /*! \brief Get the duration until expiration
     *
     * \sa setDuration()
     */
    constexpr
    std::chrono::milliseconds duration() const noexcept
    {
      return mDuration;
    }

    /*! \brief Start this timer
     */
    constexpr
    void start(TimePoint now) noexcept
    {
      mStartTime = now;
    }

    /*! \brief Returns the time passed to start()
     *
     * \sa start()
     */
    constexpr
    TimePoint startTime() const noexcept
    {
      return mStartTime;
    }

    /*! \brief
     *
     * \pre \a t must be >= initialTime
     */
    // void setCurrentTime(TimePoint t);

    /*! \brief Returns true if expired
     */
    constexpr
    bool hasExpired(TimePoint now) const noexcept
    {
      return now >= (mStartTime + mDuration);
    }

    /*! \brief Returns a time point representing the current point in time
     *
     * \sa https://en.cppreference.com/w/cpp/chrono/steady_clock/now.html
     */
    static
    TimePoint now() noexcept
    {
      return std::chrono::steady_clock::now();
    }

   private:

    TimePoint mStartTime = TimePoint( std::chrono::milliseconds(0) );
    std::chrono::milliseconds mDuration = std::chrono::milliseconds(0);

    // TimePoint mCurrentTime;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PINOUT_SIGNAL_UI_STATE_TIMER_H
