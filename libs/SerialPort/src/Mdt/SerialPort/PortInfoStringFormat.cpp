// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortInfoStringFormat.h"
#include <QLatin1String>
#include <QStringBuilder>

namespace Mdt{ namespace SerialPort{

QString PortInfoStringFormat::vendorIdentifierToString(std::optional<quint16> vid) noexcept
{
  if( vid.has_value() ){
    return QLatin1String("0x") % QString::number(*vid, 16);
  }

  return QString();
}

QString PortInfoStringFormat::vendorIdentifierToString(const QSerialPortInfo & portInfo) noexcept
{
  if( portInfo.hasVendorIdentifier() ){
    return vendorIdentifierToString( portInfo.vendorIdentifier() );
  }

  return QString();
}

QString PortInfoStringFormat::productIdentifierToString(std::optional<quint16> pid) noexcept
{
  if( pid.has_value() ){
    return QLatin1String("0x") % QString::number(*pid, 16);
  }

  return QString();
}

QString PortInfoStringFormat::productIdentifierToString(const QSerialPortInfo & portInfo) noexcept
{
  if( portInfo.hasProductIdentifier() ){
    return productIdentifierToString( portInfo.productIdentifier() );
  }

  return QString();
}

}} // namespace Mdt{ namespace SerialPort{
