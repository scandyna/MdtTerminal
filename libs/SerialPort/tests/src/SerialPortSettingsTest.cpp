// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Settings.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("baudRateHasMinimalValidity")
{
  CHECK( !Settings::baudRateHasMinimalValidity(-1) );
  CHECK( !Settings::baudRateHasMinimalValidity(0) );
  CHECK( Settings::baudRateHasMinimalValidity(1) );
}

TEST_CASE("defaultSettings")
{
  auto settings = Settings::defaultSettings();

  CHECK( settings.baudRate() == 9600 );
}