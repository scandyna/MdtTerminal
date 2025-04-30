// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/ParityStringFormat.h"
#include <QLatin1Char>
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("firstUpperCaseCharOfParity")
{
  CHECK( ParityStringFormat::firstUpperCaseCharOfParity(QSerialPort::NoParity) == QLatin1Char('N') );
}
