// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortInfo.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

bool isExistingSerialPort(const PortInfo & /*portInfo*/)
{
  return true;
}

}} // namespace Mdt{ namespace SerialPort{
