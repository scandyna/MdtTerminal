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

// #include <QDebug>

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

/*
 * Inspired by qulltoa() in qlocale_tools.cpp
 */
QString BaudRateStringFormat::number(qint32 n) noexcept
{
  assert(n >= 0);

  if(n == 0){
    return QLatin1String("0");
  }

  using size_type = QString::size_type;

  /// \todo define correct length
  QString str( 10,  QChar::fromLatin1('0') );

  size_type index = str.size() - 1;
  assert(index >= 0);

  assert(n > 0);
  quint32 un = static_cast<quint32>(n);

  while(un != 0){
    const int c = un % 10;
    const quint32 temp = un / 10;
    assert(index >= 0);
    assert(c >= 0);
    assert(c < 10);
    str[index] = QChar::fromLatin1( static_cast<char>('0' + c) );
    un = temp;
    --index;
  }
  assert( index >= 0 );
  assert( index < str.size() );

  return str.mid(index+1);
}

}} // namespace Mdt{ namespace SerialPort{
