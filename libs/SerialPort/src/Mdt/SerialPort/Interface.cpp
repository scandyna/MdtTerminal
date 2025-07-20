// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Interface.h"

namespace Mdt{ namespace SerialPort{

Interface Interface::fromStandardAndParameterValue(InterfaceStandard standard, unsigned int value) noexcept
{
  return Interface(standard, value);
}

Interface::Interface(InterfaceStandard standard, unsigned int value) noexcept
 : mStandard(standard),
   mParameterValue(value),
   mIsConfigurable(true)
{
}

}} // namespace Mdt{ namespace SerialPort{
