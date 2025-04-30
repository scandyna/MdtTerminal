// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/FlowControlStringFormat.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("flowControlToShortString")
{
  CHECK( FlowControlStringFormat::flowControlToShortString(QSerialPort::HardwareControl) == "RTS/CTS" );
  CHECK( FlowControlStringFormat::flowControlToShortString(QSerialPort::SoftwareControl) == "XON/XOFF" );
}
