// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/BmRequestType.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("DefaultConstructed")
{
  BmRequestType rt;

  CHECK( rt.value() == 0 );
  CHECK( rt.dataTransferDirection() == DataTransferDirection::HostToDevice );
}

TEST_CASE("setDataTransferDirection")
{
  BmRequestType rt;

  SECTION("initially all bits to 0")
  {
    REQUIRE( rt.value() == 0 );

    SECTION("set Device-to-host - D7 to 1")
    {
      rt.setDataTransferDirection(DataTransferDirection::DeviceToHost);

      CHECK( rt.value() == 0b1000'0000 );
      CHECK( rt.dataTransferDirection() == DataTransferDirection::DeviceToHost );
    }

    SECTION("set Host-to-device - D7 to 0")
    {
      rt.setDataTransferDirection(DataTransferDirection::HostToDevice);

      CHECK( rt.value() == 0b0000'0000 );
      CHECK( rt.dataTransferDirection() == DataTransferDirection::HostToDevice );
    }
  }

  SECTION("initially all bits to 1")
  {
    rt.setValue(0b1111'1111);
    REQUIRE( rt.value() == 0b1111'1111 );

    SECTION("set Device-to-host - D7 to 1")
    {
      rt.setDataTransferDirection(DataTransferDirection::DeviceToHost);

      CHECK( rt.value() == 0b1111'1111 );
      CHECK( rt.dataTransferDirection() == DataTransferDirection::DeviceToHost );
    }

    SECTION("set Host-to-device - D7 to 0")
    {
      rt.setDataTransferDirection(DataTransferDirection::HostToDevice);

      CHECK( rt.value() == 0b0111'1111 );
      CHECK( rt.dataTransferDirection() == DataTransferDirection::HostToDevice );
    }
  }
}

TEST_CASE("dataTransferDirection")
{
  BmRequestType rt;

  SECTION("only bit D7 to 1")
  {
    rt.setValue(0b1000'0000);

    CHECK( rt.dataTransferDirection() == DataTransferDirection::DeviceToHost );
  }

  SECTION("all bits to 1")
  {
    rt.setValue(0b1111'1111);

    CHECK( rt.dataTransferDirection() == DataTransferDirection::DeviceToHost );
  }

  SECTION("all bits except D7 to 1")
  {
    rt.setValue(0b0111'1111);

    CHECK( rt.dataTransferDirection() == DataTransferDirection::HostToDevice );
  }
}
