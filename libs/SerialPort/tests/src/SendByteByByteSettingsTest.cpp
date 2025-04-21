// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SendByteByByteSettings.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include <chrono>

using namespace Mdt::SerialPort;
using namespace std::chrono_literals;


TEST_CASE("Interval_limits")
{
  CHECK( SendByteByByteSettings::minimumRawIntervalInMilliseconds() == 1 );
  CHECK( SendByteByByteSettings::minimumInterval() == 1ms );
  CHECK( SendByteByByteSettings::maximumRawIntervalInMilliseconds() == 500 );
  CHECK( SendByteByByteSettings::maximumInterval() == 500ms );
}

TEST_CASE("disabled")
{
  const auto settings = SendByteByByteSettings::disabled();

  CHECK( !settings.isEnabled() );
}

TEST_CASE("intervalIsValid")
{
  CHECK( !SendByteByByteSettings::intervalIsValid(-1ms) );
  CHECK( !SendByteByByteSettings::intervalIsValid(0ms) );
  CHECK( SendByteByByteSettings::intervalIsValid(1ms) );
  CHECK( SendByteByByteSettings::intervalIsValid(50ms) );
  CHECK( SendByteByByteSettings::intervalIsValid(500ms) );
  CHECK( !SendByteByByteSettings::intervalIsValid(501ms) );
}

TEST_CASE("rawIntervalInMillisecondsIsValid")
{
  CHECK( !SendByteByByteSettings::rawIntervalInMillisecondsIsValid(-1) );
  CHECK( !SendByteByByteSettings::rawIntervalInMillisecondsIsValid(0) );
  CHECK( SendByteByByteSettings::rawIntervalInMillisecondsIsValid(1) );
  CHECK( SendByteByByteSettings::rawIntervalInMillisecondsIsValid(50) );
  CHECK( SendByteByByteSettings::rawIntervalInMillisecondsIsValid(500) );
  CHECK( !SendByteByByteSettings::rawIntervalInMillisecondsIsValid(501) );
}

TEST_CASE("enabledWithInterval")
{
  const auto settings = SendByteByByteSettings::enabledWithInterval(15ms);

  CHECK( settings.isEnabled() );
  CHECK( settings.interval() == 15ms );
  CHECK( settings.rawIntervalInMilliseconds() == 15 );
}

TEST_CASE("enabledWithRawIntervalInMilliseconds")
{
  const auto settings = SendByteByByteSettings::enabledWithRawIntervalInMilliseconds(20);

  CHECK( settings.isEnabled() );
  CHECK( settings.interval() == 20ms );
  CHECK( settings.rawIntervalInMilliseconds() == 20 );
}
