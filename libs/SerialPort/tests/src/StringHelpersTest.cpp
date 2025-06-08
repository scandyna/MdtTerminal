// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/StringHelpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include <limits>

using namespace Mdt::SerialPort;


TEST_CASE("stringLength")
{
  CHECK( stringLength(nullptr, 0) == 0 );
  CHECK( stringLength(nullptr, 1) == 0 );
  CHECK( stringLength(nullptr, 3) == 0 );

  CHECK( stringLength("", 0) == 0 );
  CHECK( stringLength("", 1) == 0 );
  CHECK( stringLength("", 2) == 0 );

  CHECK( stringLength("a", 0) == 0 );
  CHECK( stringLength("a", 1) == 1 );
  CHECK( stringLength("a", 2) == 1 );

  CHECK( stringLength("01234", 3) == 3 );
  CHECK( stringLength("01234", 4) == 4 );
  CHECK( stringLength("01234", 5) == 5 );
  CHECK( stringLength("01234", 6) == 5 );
  CHECK( stringLength("01234", 7) == 5 );
}

TEST_CASE("uint8_t_valueFromString")
{
  CHECK( uint8_t_valueFromString("0") == 0 );
  CHECK( uint8_t_valueFromString("1") == 1 );
  CHECK( uint8_t_valueFromString("255") == 255 );
}

TEST_CASE("uint8_t_valueFromString_ErrorTest")
{
  CHECK_THROWS_AS( uint8_t_valueFromString("-1"), std::out_of_range );
  CHECK_THROWS_AS( uint8_t_valueFromString("256"), std::out_of_range );
  CHECK_THROWS_AS( uint8_t_valueFromString("abcd"), std::invalid_argument );
}

TEST_CASE("uint16_t_valueFromString")
{
  CHECK( uint16_t_valueFromString("0") == 0 );
  CHECK( uint16_t_valueFromString("1") == 1 );
  CHECK( uint16_t_valueFromString("65535") == 65535 );
  CHECK( uint16_t_valueFromString("ffff", 16) == 0xffff );
}

TEST_CASE("uint16_t_valueFromString_ErrorTest")
{
  CHECK_THROWS_AS( uint16_t_valueFromString("-1"), std::out_of_range );
  CHECK_THROWS_AS( uint16_t_valueFromString("65536"), std::out_of_range );
  CHECK_THROWS_AS( uint16_t_valueFromString("abcd"), std::invalid_argument );
}
