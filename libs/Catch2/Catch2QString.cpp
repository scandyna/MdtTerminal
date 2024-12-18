// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Catch2QString.h"
#include <QByteArray>

std::ostream & operator <<(std::ostream & os, const QString & str)
{
  os << str.toLocal8Bit().toStdString();

  return os;
}
