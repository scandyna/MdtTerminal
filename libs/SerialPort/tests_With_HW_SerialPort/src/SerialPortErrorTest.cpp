// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SerialPort.h"
#include "Mdt/SerialPort/TestLib/TestPortInfo.h"

// #include "Mdt/SerialPort/TestLib/Helpers.h"

#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::SerialPort::TestLib::TestPortInfo;


TEST_CASE("OpenNonExistingPort")
{
  SerialPort port;

  const PortInfo portInfo = TestPortInfo::fromPortNameAndSystemLocation("NotASerialPort", "/probably/NotASerialPort");
  const auto settings = Settings::defaultSettingsWithPortInfo(portInfo);
  port.setSettings(settings);

  CHECK_THROWS_AS(port.openReadWrite(), PortOpenError);
  CHECK( !port.isOpen() );
}

TEST_CASE("OpenNonExistingMoxaUport")
{
  SerialPort port;

  TestPortInfo portInfo = TestPortInfo::fromPortNameAndSystemLocation("NotASerialPort", "/probably/NotASerialPort");
  portInfo.setVendorIdentifier(0x110a);
  portInfo.setProductIdentifier(0x1250);
  const auto settings = Settings::defaultSettingsWithPortInfo(portInfo);
  port.setSettings(settings);

  CHECK_THROWS_AS(port.openReadWrite(), PortOpenError);
  CHECK( !port.isOpen() );
}
