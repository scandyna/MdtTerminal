// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Settings.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

bool Settings::baudRateHasMinimalValidity(qint32 rate) noexcept
{
  return rate > 0;
}

bool Settings::dataBitsHasMinimalValidity(QSerialPort::DataBits bits) noexcept
{
  return bits != QSerialPort::UnknownDataBits;
}

Settings Settings::defaultSettings() noexcept
{
  Settings settings;

  settings.setBaudRate(9600);
  settings.setDataBits(QSerialPort::Data8);

  return settings;
}

void Settings::setBaudRate(qint32 rate) noexcept
{
  assert( baudRateHasMinimalValidity(rate) );

  mBaudRate = rate;
}

void Settings::setDataBits(QSerialPort::DataBits bits) noexcept
{
  assert( dataBitsHasMinimalValidity(bits) );

  mDataBits = bits;
}

}} // namespace Mdt{ namespace SerialPort{
