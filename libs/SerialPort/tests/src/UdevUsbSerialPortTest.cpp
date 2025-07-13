// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Linux/UdevUsbSerialPort.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::Linux;


TEST_CASE("defaultConstructed")
{
  UdevUsbSerialPort port;

  CHECK( !port.hasUsbBusNumber() );
  CHECK( !port.hasUsbDeviceAddress() );
  CHECK( !port.hasPortNumber() );
  CHECK( !port.hasDriverName() );
  CHECK( !port.isComplete() );
}

TEST_CASE("collectAttributes")
{
  UdevUsbSerialPort port;

  port.setUsbBusNumber(1);
  CHECK( port.hasUsbBusNumber() );
  CHECK( port.usbBusNumber() == 1 );
  CHECK( !port.isComplete() );

  port.setUsbDeviceAddress(2);
  CHECK( port.hasUsbDeviceAddress() );
  CHECK( port.usbDeviceAddress() == 2 );
  CHECK( !port.isComplete() );

  port.setPortNumber(0);
  CHECK( port.hasPortNumber() );
  CHECK( port.portNumber() == 0 );
  CHECK( !port.isComplete() );

  port.setDriverName("driverName");
  CHECK( port.hasDriverName() );
  CHECK( port.driverName() == "driverName" );

  CHECK( port.isComplete() );
}
