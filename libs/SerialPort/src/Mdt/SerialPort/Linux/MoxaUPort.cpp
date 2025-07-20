// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "MoxaUPort.h"
#include "Mdt/SerialPort/StringHelpers.h"

namespace Mdt{ namespace SerialPort{ namespace Linux{

bool isLinuxMxuportDriver(const std::string & driverName) noexcept
{
  return driverName == "mxuport";
}

bool isMoxaMxuportDriver(const std::string & driverName) noexcept
{
  return stringStartsWith(driverName, "MxUPort-") || stringStartsWith(driverName, "MxSerial-") || stringStartsWith(driverName, "MxuportG2-");
}

}}} // namespace Mdt{ namespace SerialPort{ namespace Linux{
