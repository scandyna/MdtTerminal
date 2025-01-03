// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "ParityStringFormat.h"

namespace Mdt{ namespace SerialPort{

QString ParityStringFormat::parityToString(QSerialPort::Parity parity) noexcept
{
  switch(parity){
    case QSerialPort::NoParity:
      return tr("None");
    case QSerialPort::EvenParity:
      return tr("Even");
    case QSerialPort::OddParity:
      return tr("Odd");
    case QSerialPort::SpaceParity:
      return tr("Space");
    case QSerialPort::MarkParity:
      return tr("Mark");
    case QSerialPort::UnknownParity:
      return tr("Unknown");
  }

  return QString();
}

}} // namespace Mdt{ namespace SerialPort{
