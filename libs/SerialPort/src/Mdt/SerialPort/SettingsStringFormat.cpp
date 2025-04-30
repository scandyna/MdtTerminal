// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsStringFormat.h"
#include "StopBitsStringFormat.h"
#include "ParityStringFormat.h"
#include <QStringBuilder>
#include <QLatin1Char>

namespace Mdt{ namespace SerialPort{

QString SettingsStringFormat::dpsStringFromSettings(const Settings & settings) noexcept
{
  return QString::number( settings.dataBits() ) % QLatin1Char('-')
       % ParityStringFormat::firstUpperCaseCharOfParity( settings.parity() ) % QLatin1Char('-')
       % StopBitsStringFormat::stopBitsToString( settings.stopBits() );
}

QString SettingsStringFormat::dpsStringFromPort(const QSerialPort & port) noexcept
{
  return QString::number( port.dataBits() ) % QLatin1Char('-')
       % ParityStringFormat::firstUpperCaseCharOfParity( port.parity() ) % QLatin1Char('-')
       % StopBitsStringFormat::stopBitsToString( port.stopBits() );
}

QString SettingsStringFormat::baudeRateAndDpsStringFromSettings(const Settings & settings) noexcept
{
  return QString::number( settings.baudRate() ) % QLatin1Char('-')
       % dpsStringFromSettings(settings);
}

QString SettingsStringFormat::baudeRateAndDpsStringFromPort(const QSerialPort & port) noexcept
{
  return QString::number( port.baudRate() ) % QLatin1Char('-')
       % dpsStringFromPort(port);
}

}} // namespace Mdt{ namespace SerialPort{
