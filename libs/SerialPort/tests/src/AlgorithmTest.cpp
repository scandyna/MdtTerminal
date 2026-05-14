// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Algorithm.h"
#include "Mdt/SerialPort/TestLib/TestPortInfo.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include <QString>
#include <vector>

using namespace Mdt::SerialPort;
using Mdt::SerialPort::TestLib::TestPortInfo;


TEST_CASE("isLessThanByPortName")
{
  QCollator collator;
  collator.setNumericMode(true);

  SECTION("ttyS0 < ttyS1")
  {
    const auto a = TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0");
    const auto b = TestPortInfo::fromPortNameAndSystemLocation("ttyS1", "/dev/ttyS1");
    CHECK( isLessThanByPortName(a, b, collator) );
  }

  SECTION("ttyS2 < ttyS10")
  {
    const auto a = TestPortInfo::fromPortNameAndSystemLocation("ttyS2", "/dev/ttyS2");
    const auto b = TestPortInfo::fromPortNameAndSystemLocation("ttyS10", "/dev/ttyS10");
    CHECK( isLessThanByPortName(a, b, collator) );
  }

  SECTION("COM2 < COM10")
  {
    const auto a = TestPortInfo::fromPortNameAndSystemLocation("COM2", "//./COM2");
    const auto b = TestPortInfo::fromPortNameAndSystemLocation("COM10", "//./COM10");
    CHECK( isLessThanByPortName(a, b, collator) );
  }
}

TEST_CASE("sortPortInfoListByPortName")
{
  using List = std::vector<PortInfo>;

  List list;

  SECTION("empty")
  {
    sortPortInfoListByPortName(list);

    CHECK( list.empty() );
  }

  SECTION("ttyS1,ttyS0 -> ttyS0,ttyS1")
  {
    list.push_back( TestPortInfo::fromPortNameAndSystemLocation("ttyS1", "/dev/ttyS1") );
    list.push_back( TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0") );

    sortPortInfoListByPortName(list);

    REQUIRE( list.size() == 2 );
    CHECK( list.at(0).portName() == "ttyS0" );
    CHECK( list.at(1).portName() == "ttyS1" );
  }

  SECTION("ttyS10,ttyS2 -> ttyS2,ttyS10")
  {
    list.push_back( TestPortInfo::fromPortNameAndSystemLocation("ttyS10", "/dev/ttyS10") );
    list.push_back( TestPortInfo::fromPortNameAndSystemLocation("ttyS2", "/dev/ttyS2") );

    sortPortInfoListByPortName(list);

    REQUIRE( list.size() == 2 );
    CHECK( list.at(0).portName() == "ttyS2" );
    CHECK( list.at(1).portName() == "ttyS10" );
  }
}
