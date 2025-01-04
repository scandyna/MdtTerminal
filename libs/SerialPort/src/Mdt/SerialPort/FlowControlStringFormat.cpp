// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "FlowControlStringFormat.h"

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

}} // namespace Mdt{ namespace SerialPort{
