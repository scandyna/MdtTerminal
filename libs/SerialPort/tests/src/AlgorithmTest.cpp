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
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include <QString>

using namespace Mdt::SerialPort;

/*
 * This is a simple version of TestPortInfo
 * Avoid to depend on the one in TestPortInfoListTableModel
 * (in TestLib), that has other fields.
 */
class TestPortInfo
{
 public:

  QString portName() const
  {
    return mPortName;
  }

  static
  TestPortInfo fromPortName(const QString & name)
  {
    return TestPortInfo(name);
  }

 private:

  TestPortInfo(const QString & name) noexcept
   : mPortName(name)
  {
  }

  QString mPortName;
};


TEST_CASE("isLessThanByPortName")
{
  QCollator collator;
  collator.setNumericMode(true);

  SECTION("ttyS0 < ttyS1")
  {
    const auto a = TestPortInfo::fromPortName("ttyS0");
    const auto b = TestPortInfo::fromPortName("ttyS1");
    CHECK( isLessThanByPortName(a, b, collator) );
  }

  SECTION("ttyS2 < ttyS10")
  {
    const auto a = TestPortInfo::fromPortName("ttyS2");
    const auto b = TestPortInfo::fromPortName("ttyS10");
    CHECK( isLessThanByPortName(a, b, collator) );
  }

  SECTION("COM2 < COM10")
  {
    const auto a = TestPortInfo::fromPortName("COM2");
    const auto b = TestPortInfo::fromPortName("COM10");
    CHECK( isLessThanByPortName(a, b, collator) );
  }
}

TEST_CASE("sortPortInfoListByPortName")
{
  using List = QList<TestPortInfo>;

  List list;

  SECTION("empty")
  {
    sortPortInfoListByPortName(list);

    CHECK( list.isEmpty() );
  }

  SECTION("ttyS1,ttyS0 -> ttyS0,ttyS1")
  {
    list.append( TestPortInfo::fromPortName("ttyS1") );
    list.append( TestPortInfo::fromPortName("ttyS0") );

    sortPortInfoListByPortName(list);

    REQUIRE( list.size() == 2 );
    CHECK( list.at(0).portName() == "ttyS0" );
    CHECK( list.at(1).portName() == "ttyS1" );
  }

  SECTION("ttyS10,ttyS2 -> ttyS2,ttyS10")
  {
    list.append( TestPortInfo::fromPortName("ttyS10") );
    list.append( TestPortInfo::fromPortName("ttyS2") );

    sortPortInfoListByPortName(list);

    REQUIRE( list.size() == 2 );
    CHECK( list.at(0).portName() == "ttyS2" );
    CHECK( list.at(1).portName() == "ttyS10" );
  }
}
