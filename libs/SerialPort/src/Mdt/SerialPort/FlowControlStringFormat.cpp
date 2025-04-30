// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "FlowControlStringFormat.h"
#include <QLatin1Literal>

namespace Mdt{ namespace SerialPort{

QString FlowControlStringFormat::flowControlToString(QSerialPort::FlowControl control) noexcept
{
  switch(control){
    case QSerialPort::NoFlowControl:
      return tr("None");
    case QSerialPort::HardwareControl:
      return tr("Hardware (RTS/CTS)");
    case QSerialPort::SoftwareControl:
      return tr("Software (XON/XOFF)");
    case QSerialPort::UnknownFlowControl:
      return tr("Unknown");
  }

  return QString();
}

QString FlowControlStringFormat::flowControlToShortString(QSerialPort::FlowControl control) noexcept
{
  switch(control){
    case QSerialPort::HardwareControl:
      return QLatin1String("RTS/CTS");
    case QSerialPort::SoftwareControl:
      return QLatin1String("XON/XOFF");
    case QSerialPort::NoFlowControl:
    case QSerialPort::UnknownFlowControl:
      break;
  }

  return QString();
}

}} // namespace Mdt{ namespace SerialPort{
