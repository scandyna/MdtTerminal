// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/InterfaceList.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("default_constructed")
{
  InterfaceList list;

  CHECK( list.count() == 1 );
  CHECK( !list.canSelectInterface() );
  CHECK( list.interfaceAt(0).standard() == InterfaceStandard::RS_232 );
}

TEST_CASE("fromMoxaProductIdentifier")
{
  SECTION("UPort_1250")
  {
    const auto list = InterfaceList::fromMoxaProductIdentifier(0x1250);

    CHECK( list.count() == 4 );
  }

  SECTION("other")
  {
    const auto list = InterfaceList::fromMoxaProductIdentifier(0x1234);

    CHECK( list.count() == 1 );
    CHECK( !list.canSelectInterface() );
    CHECK( list.interfaceAt(0).standard() == InterfaceStandard::RS_232 );
  }
}

TEST_CASE("moxaUPort_1250_1450_1650")
{
  const auto list = InterfaceList::moxaUPort_1250_1450_1650();

  CHECK( list.count() == 4 );
  CHECK( list.canSelectInterface() );
  CHECK( list.interfaceAt(0).standard() == InterfaceStandard::RS_232 );
  CHECK( list.interfaceAt(0).parameterValue() == 0x00 );
  CHECK( list.interfaceAt(1).standard() == InterfaceStandard::RS_485_2W );
  CHECK( list.interfaceAt(1).parameterValue() == 0x01 );
  CHECK( list.interfaceAt(2).standard() == InterfaceStandard::RS_422 );
  CHECK( list.interfaceAt(2).parameterValue() == 0x02 );
  CHECK( list.interfaceAt(3).standard() == InterfaceStandard::RS_485_4W );
  CHECK( list.interfaceAt(3).parameterValue() == 0x03 );
}

TEST_CASE("findIndexOfParameterValue")
{
  // SECTION("Default list")
  // {
  //   InterfaceList list;
  //
  //   CHECK( list.findIndexOfParameterValue(0x00) < 0 );
  //   CHECK( list.findIndexOfParameterValue(0x01) < 0 );
  // }

  SECTION("Moxa UPort_1250")
  {
    const auto list = InterfaceList::moxaUPort_1250_1450_1650();

    CHECK( list.findIndexOfParameterValue(0x00) == 0 );
    CHECK( list.findIndexOfParameterValue(0x01) == 1 );
    CHECK( list.findIndexOfParameterValue(0x02) == 2 );
    CHECK( list.findIndexOfParameterValue(0x03) == 3 );
    CHECK( !list.findIndexOfParameterValue(0x04).has_value() );
  }
}

TEST_CASE("fromVendorIdentifierAndProductIdentifier")
{
  SECTION("Moxa UPort 1250")
  {
    const auto list = InterfaceList::fromVendorIdentifierAndProductIdentifier(0x110a, 0x1250);

    CHECK( list.count() == 4 );
    CHECK( list.canSelectInterface() );
    CHECK( list.interfaceAt(0).standard() == InterfaceStandard::RS_232 );
    CHECK( list.interfaceAt(1).standard() == InterfaceStandard::RS_485_2W );
    CHECK( list.interfaceAt(2).standard() == InterfaceStandard::RS_422 );
    CHECK( list.interfaceAt(3).standard() == InterfaceStandard::RS_485_4W );
  }

  SECTION("unknown")
  {
    const auto list = InterfaceList::fromVendorIdentifierAndProductIdentifier(0, 0);

    CHECK( list.count() == 1 );
    CHECK( !list.canSelectInterface() );
    CHECK( list.interfaceAt(0).standard() == InterfaceStandard::RS_232 );
  }
}

TEST_CASE("findIndexOfStandard")
{
  SECTION("Default list having only a RS-232 interface")
  {
    InterfaceList list;
    REQUIRE( list.count() == 1 );

    CHECK( list.findIndexOfStandard(InterfaceStandard::RS_232) == 0 );
    CHECK( !list.findIndexOfStandard(InterfaceStandard::RS_485_2W).has_value() );
  }

  SECTION("Moxa UPort 1250")
  {
    const auto list = InterfaceList::fromVendorIdentifierAndProductIdentifier(0x110a, 0x1250);
    REQUIRE( list.count() == 4 );

    CHECK( list.findIndexOfStandard(InterfaceStandard::RS_232) == 0 );
    CHECK( list.findIndexOfStandard(InterfaceStandard::RS_485_2W) == 1 );
  }
}
