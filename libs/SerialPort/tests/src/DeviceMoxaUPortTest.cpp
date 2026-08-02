// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Device/MoxaUPort.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::Device;
using Mdt::SerialPort::InterfaceStandard;


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

TEST_CASE("interfaceStandardFromMoxaUport_1250_1450_1650_ParameterValue")
{
  CHECK( interfaceStandardFromMoxaUport_1250_1450_1650_ParameterValue(0x0) == InterfaceStandard::RS_232 );
  CHECK( interfaceStandardFromMoxaUport_1250_1450_1650_ParameterValue(0x1) == InterfaceStandard::RS_485_2W );
  CHECK( interfaceStandardFromMoxaUport_1250_1450_1650_ParameterValue(0x2) == InterfaceStandard::RS_422 );
  CHECK( interfaceStandardFromMoxaUport_1250_1450_1650_ParameterValue(0x3) == InterfaceStandard::RS_485_4W );
}
