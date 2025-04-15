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

QString InterfaceStringFormat::standardName(InterfaceStandard standard) noexcept
{
  switch(standard){
    case InterfaceStandard::RS_232:
      return rs232Name();
    case InterfaceStandard::RS_422:
      return rs422Name();
    case InterfaceStandard::RS_485_2W:
      return rs485TwoWireName();
    case InterfaceStandard::RS_485_4W:
      return rs485TwoWireName();
  }

  return QString();
}

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
