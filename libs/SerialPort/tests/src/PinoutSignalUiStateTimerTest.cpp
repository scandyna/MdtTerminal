// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PinoutSignalUiStateTimer.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include <thread>

using namespace Mdt::SerialPort;
using namespace std::chrono_literals;
using TimePoint = PinoutSignalUiStateTimer::TimePoint;


TEST_CASE("initialState")
{
  PinoutSignalUiStateTimer timer;

  CHECK( timer.duration() == 0ms );
  CHECK( timer.startTime() == TimePoint(0ms) );
}

TEST_CASE("basicTest")
{
  PinoutSignalUiStateTimer timer;
  timer.setDuration(100ms);

  timer.start( TimePoint(20ms) );

  CHECK( !timer.hasExpired( TimePoint(20ms) ) );
  CHECK( !timer.hasExpired( TimePoint(100ms) ) );
  CHECK( timer.hasExpired( TimePoint(120ms) ) );
  CHECK( timer.hasExpired( TimePoint(150ms) ) );
}

TEST_CASE("now")
{
  PinoutSignalUiStateTimer timer;
  timer.setDuration(50ms);

  TimePoint now = PinoutSignalUiStateTimer::now();

  timer.start(now);
  CHECK( !timer.hasExpired(now) );

  std::this_thread::sleep_for(100ms);

  now = PinoutSignalUiStateTimer::now();
  CHECK( timer.hasExpired(now) );
}
