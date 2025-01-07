// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "StopBitsStringFormat.h"
#include <QLatin1String>

namespace Mdt{ namespace SerialPort{

QString StopBitsStringFormat::stopBitsToString(QSerialPort::StopBits bits) noexcept
{
  switch(bits){
    case QSerialPort::OneStop:
      return QLatin1String("1");
    case QSerialPort::OneAndHalfStop:
      return QLatin1String("1.5");
    case QSerialPort::TwoStop:
      return QLatin1String("2");
    case QSerialPort::UnknownStopBits:
      return tr("Unknown");
  }

  return QString();
}

}} // namespace Mdt{ namespace SerialPort{
