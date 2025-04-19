// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "BaudRateStringFormat.h"
#include <QStringBuilder>
#include <QLatin1String>
#include <QChar>
#include <cassert>

namespace Mdt{ namespace SerialPort{

QString BaudRateStringFormat::toHumanFriendlyString(qint32 rate) noexcept
{
  assert(rate > 0);

  if(rate < 10'000){
    return toHumanFriendlyString_bps(rate);
  }
  if(rate < 1'000'000){
    return toHumanFriendlyString_kbps(rate);
  }

  return toHumanFriendlyString_Mbps(rate);
}

QString BaudRateStringFormat::toHumanFriendlyString_bps(qint32 rate) noexcept
{
  assert(rate > 0);

  return QString::number(rate) % QLatin1String(" b/s");
}

QString BaudRateStringFormat::toHumanFriendlyString_kbps(qint32 rate) noexcept
{
  assert(rate > 0);

  return QString::number(static_cast<double>(rate) / 1'000.) % QLatin1String(" kb/s");
}

QString BaudRateStringFormat::toHumanFriendlyString_Mbps(qint32 rate) noexcept
{
  assert(rate > 0);

  return QString::number(static_cast<double>(rate) / 1'000'000.) % QLatin1String(" Mb/s");
}

}} // namespace Mdt{ namespace SerialPort{
