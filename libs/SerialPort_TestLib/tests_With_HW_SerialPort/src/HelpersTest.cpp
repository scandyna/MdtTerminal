// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/TestLib/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::TestLib;

/*
 * If we run this test, we know we have at least 1 real serial port on the system
 */
TEST_CASE("openFirstAvailableSerialPort")
{
  QSerialPort port;
  REQUIRE( !port.isOpen() );

  CHECK( openFirstAvailableSerialPort(port, QSerialPort::ReadOnly) );

  CHECK( !port.portName().isEmpty() );
  CHECK( port.isOpen() );
}
