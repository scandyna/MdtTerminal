// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "InterfaceStringFormat.h"
#include <QLatin1String>

namespace Mdt{ namespace SerialPort{

QString InterfaceStringFormat::rs232Name() noexcept
{
  return QLatin1String("RS-232");
}

QString InterfaceStringFormat::rs422Name() noexcept
{
  return QLatin1String("RS-422");
}

QString InterfaceStringFormat::rs485TwoWireName() noexcept
{
  return tr("RS-485 2 wire");
}

QString InterfaceStringFormat::rs485FourWireName() noexcept
{
  return tr("RS-485 4 wire");
}

}} // namespace Mdt{ namespace SerialPort{
