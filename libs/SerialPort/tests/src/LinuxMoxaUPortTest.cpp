// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Linux/MoxaUPort.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::Linux;


TEST_CASE("isLinuxMxuportDriver")
{
  CHECK( !isLinuxMxuportDriver("") );
  CHECK( !isLinuxMxuportDriver("usb") );
  CHECK( !isLinuxMxuportDriver("MxSerial-2P") );
  CHECK( !isLinuxMxuportDriver("MxUPort-2P") );
  CHECK( isLinuxMxuportDriver("mxuport") );
}

TEST_CASE("isMoxaMxuportDriver")
{
  CHECK( !isMoxaMxuportDriver("") );
  CHECK( !isMoxaMxuportDriver("usb") );
  CHECK( !isMoxaMxuportDriver("mxuport") );
  CHECK( isMoxaMxuportDriver("MxSerial-2P") );
  CHECK( isMoxaMxuportDriver("MxUPort-2P") );
  CHECK( isMoxaMxuportDriver("MxUPort-4P") );
  CHECK( isMoxaMxuportDriver("MxuportG2-2P") );
}
