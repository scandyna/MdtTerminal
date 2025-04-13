// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Interface.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("fromNameAndParameterValue")
{
  const auto rs422 = Interface::fromNameAndParameterValue("RS-422", 1);

  CHECK( rs422.name() == "RS-422" );
  CHECK( rs422.parameterValue() == 1 );
}
