// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/NumericLimits.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("uint8_t_canHoldValueOf_size_t")
{
  SECTION("0")
  {
    REQUIRE( uint8_t_canHoldValueOf_size_t(0) );
  }

  SECTION("1")
  {
    REQUIRE( uint8_t_canHoldValueOf_size_t(1) );
  }

  SECTION("uint8_t max")
  {
    constexpr std::size_t intMax = std::numeric_limits<uint8_t>::max();

    REQUIRE( uint8_t_canHoldValueOf_size_t(intMax) );
  }

  SECTION("uint8_t max + 1")
  {
    constexpr std::size_t value = std::numeric_limits<uint8_t>::max() + static_cast<std::size_t>(1);

    REQUIRE( !uint8_t_canHoldValueOf_size_t(value) );
  }
}

TEST_CASE("uint8_t_from_size_t")
{
  SECTION("0")
  {
    REQUIRE( uint8_t_from_size_t(0) == 0 );
  }

  SECTION("1")
  {
    REQUIRE( uint8_t_from_size_t(1) == 1 );
  }

  SECTION("int max value")
  {
    constexpr std::size_t intMax = std::numeric_limits<uint8_t>::max();

    REQUIRE( uint8_t_from_size_t(intMax) == intMax );
  }
}
