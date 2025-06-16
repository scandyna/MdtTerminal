// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/BitManipulationHelpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


enum class TestBit3Enum : uint8_t
{
  On = 0b0000'1000,
  Off = 0b0000'0000
};

constexpr
uint8_t TestBit3EnumMask = 0b0000'1000;


TEST_CASE("applyFlags_uint8_t_flags")
{
  uint8_t value = 0;
  uint8_t flags = 0;

  SECTION("manipulate bit 7")
  {
    uint8_t mask = 0b1000'0000;

    value = 0b0000'1010;
    flags = 0b1000'0000;
    CHECK( applyFlags(value, mask, flags) == 0b1000'1010 );

    value = 0b1000'1010;
    flags = 0b0000'0000;
    CHECK( applyFlags(value, mask, flags) == 0b0000'1010 );

    value = 0b0000'1010;
    flags = 0b0000'0000;
    CHECK( applyFlags(value, mask, flags) == 0b0000'1010 );

    value = 0b1000'1010;
    flags = 0b1000'0000;
    CHECK( applyFlags(value, mask, flags) == 0b1000'1010 );
  }

  SECTION("manipulate bit 6 and 5")
  {
    uint8_t mask = 0b0110'0000;

    value = 0b0100'1010;
    flags = 0b0110'0000;
    CHECK( applyFlags(value, mask, flags) == 0b0110'1010 );

    value = 0b0100'1010;
    flags = 0b0000'0000;
    CHECK( applyFlags(value, mask, flags) == 0b0000'1010 );
  }
}

TEST_CASE("applyFlags_enum_flags")
{
  uint8_t value = 0b0000'0000;

  CHECK( applyFlags(value, TestBit3EnumMask, TestBit3Enum::On) == 0b0000'1000 );
  CHECK( applyFlags(value, TestBit3EnumMask, TestBit3Enum::Off) == 0b0000'0000 );
}
