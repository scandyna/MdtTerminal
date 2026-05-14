// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortInfoStringFormat.h"
#include <QLatin1String>
#include <QStringBuilder>

namespace Mdt{ namespace SerialPort{

QString PortInfoStringFormat::vendorIdentifierToString(std::optional<uint16_t> vid) noexcept
{
  if( vid.has_value() ){
    return QLatin1String("0x") % QString::number(*vid, 16);
  }

  return QString();
}

QString PortInfoStringFormat::vendorIdentifierToString(const PortInfo & portInfo) noexcept
{
  return vendorIdentifierToString( portInfo.vendorIdentifierIfAvailable() );
}

QString PortInfoStringFormat::productIdentifierToString(std::optional<uint16_t> pid) noexcept
{
  if( pid.has_value() ){
    return QLatin1String("0x") % QString::number(*pid, 16);
  }

  return QString();
}

QString PortInfoStringFormat::productIdentifierToString(const PortInfo & portInfo) noexcept
{
  return productIdentifierToString( portInfo.productIdentifierIfAvailable() );
}

}} // namespace Mdt{ namespace SerialPort{
