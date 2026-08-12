// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Interface.h"

namespace Mdt{ namespace SerialPort{

Interface Interface::fromStandardAndParameterValue(InterfaceStandard standard, uint16_t value) noexcept
{
  return Interface(standard, value, true);
}

Interface Interface::systemHandledOnly()
{
  return Interface(InterfaceStandard::System, 0, false);
}

Interface::Interface(InterfaceStandard standard, uint16_t value, bool isConfigurable) noexcept
 : mStandard(standard),
   mParameterValue(value),
   mIsConfigurable(isConfigurable)
{
}

}} // namespace Mdt{ namespace SerialPort{
