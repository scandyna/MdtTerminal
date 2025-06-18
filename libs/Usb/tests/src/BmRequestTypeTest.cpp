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
  CHECK( rt.type() == RequestType::Standard );
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

/*  00: 0
 *  01: 1
 *  10: 2
 *  11: 3
 */
TEST_CASE("setType")
{
  BmRequestType rt;

  SECTION("initially all bits to 0")
  {
    REQUIRE( rt.value() == 0 );

    SECTION("00 - 1 - Standard")
    {
      rt.setType(RequestType::Standard);

      CHECK( rt.value() == 0b0000'0000 );
    }

    SECTION("01 - 1 - Class")
    {
      rt.setType(RequestType::Class);

      CHECK( rt.value() == 0b0010'0000 );
    }

    SECTION("10 - 1 - Vendor")
    {
      rt.setType(RequestType::Vendor);

      CHECK( rt.value() == 0b0100'0000 );
    }

    SECTION("11 - 1 - Reserved")
    {
      rt.setType(RequestType::Reserved);

      CHECK( rt.value() == 0b0110'0000 );
    }
  }

  SECTION("initially all bits to 1")
  {
    rt.setValue(0b1111'1111);
    REQUIRE( rt.value() == 0b1111'1111 );

    SECTION("00 - 1 - Standard")
    {
      rt.setType(RequestType::Standard);

      CHECK( rt.value() == 0b1001'1111 );
    }

    SECTION("11 - 1 - Reserved")
    {
      rt.setType(RequestType::Reserved);

      CHECK( rt.value() == 0b1111'1111 );
    }
  }
}

/*  00: 0
 *  01: 1
 *  10: 2
 *  11: 3
 */
TEST_CASE("type")
{
  BmRequestType rt;

  SECTION("only bits 6 and 5 to 1")
  {
    rt.setValue(0b0110'0000);

    CHECK( rt.type() == RequestType::Reserved );
  }

  SECTION("all bits to 1")
  {
    rt.setValue(0b1111'1111);

    CHECK( rt.type() == RequestType::Reserved );
  }

  SECTION("all bits except 6 and 5 to 1")
  {
    rt.setValue(0b1001'1111);

    CHECK( rt.type() == RequestType::Standard );
  }

  SECTION("01 - 1 - Class")
  {
    rt.setValue(0b0010'0000);

    CHECK( rt.type() == RequestType::Class );
  }

  SECTION("10 - 2 - Vendor")
  {
    rt.setValue(0b0100'0000);

    CHECK( rt.type() == RequestType::Vendor );
  }
}


TEST_CASE("setRecipient")
{
  BmRequestType rt;

  SECTION("initially all bits to 0")
  {
    REQUIRE( rt.value() == 0 );

    SECTION("0 0000 - 0 - Device")
    {
      rt.setRecipient(RequestRecipient::Device);

      CHECK( rt.value() == 0b0000'0000 );
    }

    SECTION("1 1111 - 31 - Vendor specific")
    {
      rt.setRecipient(RequestRecipient::VendorSpecific);

      CHECK( rt.value() == 0b0001'1111 );
    }
  }

  SECTION("initially all bits to 1")
  {
    rt.setValue(0b1111'1111);
    REQUIRE( rt.value() == 0b1111'1111 );

    SECTION("0 0000 - 0 - Device")
    {
      rt.setRecipient(RequestRecipient::Device);

      CHECK( rt.value() == 0b1110'0000 );
    }

    SECTION("1 1111 - 31 - Vendor specific")
    {
      rt.setRecipient(RequestRecipient::VendorSpecific);

      CHECK( rt.value() == 0b1111'1111 );
    }
  }
}

/*  0'0000: 0
 *  0'0001: 1
 *  0'0010: 2
 *  0'0011: 3
 *  1'1111: 31
 */
TEST_CASE("recipient")
{
  BmRequestType rt;

  SECTION("ony bits 4 to 0 to 1 - 31")
  {
    rt.setValue(0b0001'1111);

    CHECK( rt.recipient() == RequestRecipient::VendorSpecific );
  }

  SECTION("all bits to 1")
  {
    rt.setValue(0b1111'1111);

    CHECK( rt.recipient() == RequestRecipient::VendorSpecific );
  }

  SECTION("0 0000 - 0 - Device")
  {
    rt.setValue(0b0000'0000);

    CHECK( rt.recipient() == RequestRecipient::Device );
  }

  SECTION("0 0001 - 1 - Interface")
  {
    rt.setValue(0b0000'0001);

    CHECK( rt.recipient() == RequestRecipient::Interface );
  }

  SECTION("0 0010 - 2 - Endpoint")
  {
    rt.setValue(0b0000'0010);

    CHECK( rt.recipient() == RequestRecipient::Endpoint );
  }

  SECTION("0 0011 - 3 - Other")
  {
    rt.setValue(0b0000'0011);

    CHECK( rt.recipient() == RequestRecipient::Other );
  }
}
