// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PortSetup.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("BasicTest")
{
  const auto portList = QSerialPortInfo::availablePorts();
  REQUIRE( !portList.isEmpty() );
  const auto portInfo = PortInfo::fromQSerialPortInfo( portList.at(0) );
  const auto interface = Interface::fromStandardAndParameterValue(InterfaceStandard::RS_232, 0);

  PortSetup ps;

  ps.fetchPortInformations(portInfo);
  ps.configureInterfaceBeforeOpenPortIfRequired(interface);
}
