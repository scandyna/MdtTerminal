// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_CATCH2_QSTRING_H
#define MDT_CATCH2_QSTRING_H

#include <QString>
#include <ostream>

std::ostream & operator <<(std::ostream & os, const QString & str);

#endif // #ifndef MDT_CATCH2_QSTRING_H
