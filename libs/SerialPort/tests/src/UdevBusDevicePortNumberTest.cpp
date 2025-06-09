// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Unix/UdevBusDevicePortNumber.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::Unix;


TEST_CASE("isComplete")
{
  UdevBusDevicePortNumber x;
  CHECK( !x.isComplete() );

  x.busNumber = 1;
  CHECK( !x.isComplete() );

  x.deviceNumber = 2;
  CHECK( x.isComplete() );

  x.portNumber = 0;
  CHECK( x.isComplete() );
}
