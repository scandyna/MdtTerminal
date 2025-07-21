// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
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

  PortSetup ps( portList.at(0) );

  if( ps.shouldConfigureInterfaceBeforeOpenPort() ){
    const auto interface = Interface::fromStandardAndParameterValue(InterfaceStandard::RS_232, 0);
    ps.configureInterfaceBeforeOpenPort(interface);
  }
}
