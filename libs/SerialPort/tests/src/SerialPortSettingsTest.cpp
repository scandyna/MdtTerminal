// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Settings.h"
#include "Mdt/SerialPort/TestLib/TestPortInfo.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::SerialPort::TestLib::TestPortInfo;


TEST_CASE("baudRateHasMinimalValidity")
{
  CHECK( !Settings::baudRateHasMinimalValidity(-1) );
  CHECK( !Settings::baudRateHasMinimalValidity(0) );
  CHECK( Settings::baudRateHasMinimalValidity(1) );
}

TEST_CASE("dataBitsHasMinimalValidity")
{
  CHECK( Settings::dataBitsHasMinimalValidity(QSerialPort::Data5) );
}

TEST_CASE("parityHasMinimalValidity")
{
  CHECK( Settings::parityHasMinimalValidity(QSerialPort::OddParity) );
}

TEST_CASE("flowControlHasMinimalValidity")
{
  CHECK( Settings::flowControlHasMinimalValidity(QSerialPort::SoftwareControl) );
}

TEST_CASE("stopBitsHasMinimalValidity")
{
  CHECK( Settings::stopBitsHasMinimalValidity(QSerialPort::TwoStop) );
  if constexpr( oneAndHalfStopBitsIsSupported() ){
    CHECK( Settings::stopBitsHasMinimalValidity(QSerialPort::OneAndHalfStop) );
  }else{
    CHECK( !Settings::stopBitsHasMinimalValidity(QSerialPort::OneAndHalfStop) );
  }
}

TEST_CASE("defaultSettings")
{
  auto settings = Settings::defaultSettings();

  CHECK( !settings.hasPortInfo() );
  CHECK( settings.portName().isEmpty() );
  CHECK( settings.baudRate() == 9600 );
  CHECK( settings.dataBits() == QSerialPort::Data8 );
  CHECK( settings.parity() == QSerialPort::NoParity );
  CHECK( settings.flowControl() == QSerialPort::NoFlowControl );
  CHECK( settings.stopBits() == QSerialPort::OneStop );
  CHECK( settings.interfaceStandard() == InterfaceStandard::RS_232 );
}

TEST_CASE("defaultSettingsWithPortInfo")
{
  auto settings = Settings::defaultSettingsWithPortInfo( TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0") );

  CHECK( settings.hasPortInfo() );
  CHECK( settings.portInfo().portName() == "ttyS0" );
  CHECK( settings.portName() == "ttyS0" );
  CHECK( settings.portInfo().systemLocation() == "/dev/ttyS0" );
  CHECK( settings.baudRate() == 9600 );
  CHECK( settings.dataBits() == QSerialPort::Data8 );
  CHECK( settings.parity() == QSerialPort::NoParity );
  CHECK( settings.flowControl() == QSerialPort::NoFlowControl );
  CHECK( settings.stopBits() == QSerialPort::OneStop );
  CHECK( settings.interfaceStandard() == InterfaceStandard::RS_232 );
}
