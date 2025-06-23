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
using namespace std::chrono_literals;


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

TEST_CASE("unsigned_int_canHoldValueOf_std_chrono_milliseconds")
{
  SECTION("-1ms")
  {
    CHECK( !unsigned_int_canHoldValueOf_std_chrono_milliseconds(-1ms) );
  }

  SECTION("0ms")
  {
    CHECK( unsigned_int_canHoldValueOf_std_chrono_milliseconds(0ms) );
  }

  SECTION("1ms")
  {
    CHECK( unsigned_int_canHoldValueOf_std_chrono_milliseconds(1ms) );
  }

  /*
   * std::chrono::milliseconds::rep should be at least int45 -> probably int64
   * unsigned int is at least uint16 -> probably uint32 on 64bit platforms
   *
   * If another platform (ex. 32bits) is targetted, this test should be reviewed.
   *
   * https://en.cppreference.com/w/cpp/chrono/duration.html
   * https://en.cppreference.com/w/cpp/language/types.html
   */
  SECTION("max")
  {
    constexpr std::chrono::milliseconds::rep r = std::numeric_limits<unsigned int>::max();
    constexpr std::chrono::milliseconds d(r);

    CHECK( unsigned_int_canHoldValueOf_std_chrono_milliseconds(d) );
  }
}

TEST_CASE("unsigned_int_from_std_chrono_milliseconds")
{
  SECTION("0")
  {
    CHECK( unsigned_int_from_std_chrono_milliseconds(0ms) == 0 );
  }

  SECTION("1")
  {
    CHECK( unsigned_int_from_std_chrono_milliseconds(1ms) == 1 );
  }

  SECTION("1'000")
  {
    CHECK( unsigned_int_from_std_chrono_milliseconds(1'000ms) == 1'000 );
  }

  SECTION("1'000'000")
  {
    CHECK( unsigned_int_from_std_chrono_milliseconds(1'000'000ms) == 1'000'000 );
  }
}
