// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "ParityStringFormat.h"
#include <QLatin1Char>

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
  }

  return QString();
}

QChar ParityStringFormat::firstUpperCaseCharOfParity(QSerialPort::Parity parity) noexcept
{
  switch(parity){
    case QSerialPort::NoParity:
      return QLatin1Char('N');
    case QSerialPort::EvenParity:
      return QLatin1Char('E');
    case QSerialPort::OddParity:
      return QLatin1Char('O');
    case QSerialPort::SpaceParity:
      return QLatin1Char('S');
    case QSerialPort::MarkParity:
      return QLatin1Char('M');
  }

  return QChar();
}

}} // namespace Mdt{ namespace SerialPort{
