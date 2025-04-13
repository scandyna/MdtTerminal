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

Interface Interface::fromNameAndParameterValue(const QString & name, unsigned int value) noexcept
{
  return Interface(name, value);
}

Interface::Interface(const QString & name, unsigned int value) noexcept
 : mName(name),
   mParameterValue(value)
{
}

}} // namespace Mdt{ namespace SerialPort{
