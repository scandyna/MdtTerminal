// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Device/MoxaUPort.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::Device;


TEST_CASE("vendorIdentifierIsMoxa")
{
  CHECK( !vendorIdentifierIsMoxa(0x1250) );
  CHECK( vendorIdentifierIsMoxa(0x110A) );
}

TEST_CASE("productIdentifierIsMoxaUPort_1250_1450_1650")
{
  CHECK( productIdentifierIsMoxaUPort_1250_1450_1650(0x1250) );
  CHECK( productIdentifierIsMoxaUPort_1250_1450_1650(0x1251) );
  CHECK( !productIdentifierIsMoxaUPort_1250_1450_1650(0x1410) );
  CHECK( productIdentifierIsMoxaUPort_1250_1450_1650(0x1450) );
  CHECK( productIdentifierIsMoxaUPort_1250_1450_1650(0x1451) );
  CHECK( !productIdentifierIsMoxaUPort_1250_1450_1650(0x1618) );
  CHECK( productIdentifierIsMoxaUPort_1250_1450_1650(0x1658) );
  CHECK( !productIdentifierIsMoxaUPort_1250_1450_1650(0x1613) );
  CHECK( productIdentifierIsMoxaUPort_1250_1450_1650(0x1653) );
}
