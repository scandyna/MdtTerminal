// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/BaudRateStringFormat.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("toHumanFriendlyString")
{
  SECTION("rates below 10'000")
  {
    CHECK( BaudRateStringFormat::toHumanFriendlyString(50) == "50 b/s" );
    CHECK( BaudRateStringFormat::toHumanFriendlyString(9600) == "9600 b/s" );
    CHECK( BaudRateStringFormat::toHumanFriendlyString(9999) == "9999 b/s" );
  }

  SECTION("rates from 10'000 and below 1'000'000")
  {
    CHECK( BaudRateStringFormat::toHumanFriendlyString(10'000) == "10 kb/s" );
    CHECK( BaudRateStringFormat::toHumanFriendlyString(19'200) == "19.2 kb/s" );
    CHECK( BaudRateStringFormat::toHumanFriendlyString(115'200) == "115.2 kb/s" );
    CHECK( BaudRateStringFormat::toHumanFriendlyString(500'000) == "500 kb/s" );
    CHECK( BaudRateStringFormat::toHumanFriendlyString(921'600) == "921.6 kb/s" );
    CHECK( BaudRateStringFormat::toHumanFriendlyString(999'999) == "999.999 kb/s" );
  }

  SECTION("rates from 1'000'000")
  {
    CHECK( BaudRateStringFormat::toHumanFriendlyString(1'000'000) == "1 Mb/s" );
    CHECK( BaudRateStringFormat::toHumanFriendlyString(1'152'000) == "1.152 Mb/s" );
    CHECK( BaudRateStringFormat::toHumanFriendlyString(3'500'000) == "3.5 Mb/s" );
    CHECK( BaudRateStringFormat::toHumanFriendlyString(4'000'000) == "4 Mb/s" );
  }
}

TEST_CASE("number")
{
  CHECK( BaudRateStringFormat::number(0) == "0" );
  CHECK( BaudRateStringFormat::number(1) == "1" );
  CHECK( BaudRateStringFormat::number(2) == "2" );
  CHECK( BaudRateStringFormat::number(5) == "5" );
  CHECK( BaudRateStringFormat::number(9) == "9" );
  CHECK( BaudRateStringFormat::number(10) == "10" );
  CHECK( BaudRateStringFormat::number(11) == "11" );
  CHECK( BaudRateStringFormat::number(99) == "99" );
  CHECK( BaudRateStringFormat::number(100) == "100" );
  CHECK( BaudRateStringFormat::number(101) == "101" );
  CHECK( BaudRateStringFormat::number(999) == "999" );
  CHECK( BaudRateStringFormat::number(1'000) == "1000" );
  CHECK( BaudRateStringFormat::number(1'001) == "1001" );
}
