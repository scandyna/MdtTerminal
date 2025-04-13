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
#include "Mdt/SerialPort/InterfaceStringFormat.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("default_constructed")
{
  InterfaceList list;

  CHECK( list.count() == 1 );
  CHECK( !list.canSelectInterface() );
  CHECK( list.interfaceAt(0).name() == InterfaceStringFormat::rs232Name() );
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
    CHECK( list.interfaceAt(0).name() == InterfaceStringFormat::rs232Name() );
  }
}

TEST_CASE("moxaUPort_1250_1450_1650")
{
  const auto list = InterfaceList::moxaUPort_1250_1450_1650();

  CHECK( list.count() == 4 );
  CHECK( list.canSelectInterface() );
  CHECK( list.interfaceAt(0).name() == InterfaceStringFormat::rs232Name() );
  CHECK( list.interfaceAt(0).parameterValue() == 0x00 );
  CHECK( list.interfaceAt(1).name() == InterfaceStringFormat::rs485TwoWireName() );
  CHECK( list.interfaceAt(1).parameterValue() == 0x01 );
  CHECK( list.interfaceAt(2).name() == InterfaceStringFormat::rs422Name() );
  CHECK( list.interfaceAt(2).parameterValue() == 0x02 );
  CHECK( list.interfaceAt(3).name() == InterfaceStringFormat::rs485FourWireName() );
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
    CHECK( list.interfaceAt(0).name() == InterfaceStringFormat::rs232Name() );
    CHECK( list.interfaceAt(1).name() == InterfaceStringFormat::rs485TwoWireName() );
    CHECK( list.interfaceAt(2).name() == InterfaceStringFormat::rs422Name() );
    CHECK( list.interfaceAt(3).name() == InterfaceStringFormat::rs485FourWireName() );
  }

  SECTION("unknown")
  {
    const auto list = InterfaceList::fromVendorIdentifierAndProductIdentifier(0, 0);

    CHECK( list.count() == 1 );
    CHECK( !list.canSelectInterface() );
    CHECK( list.interfaceAt(0).name() == InterfaceStringFormat::rs232Name() );
  }
}
