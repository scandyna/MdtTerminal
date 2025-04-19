// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_BAUD_RATE_STRING_FORMAT_H
#define MDT_SERIAL_PORT_BAUD_RATE_STRING_FORMAT_H

#include "mdt_serialport_export.h"
#include <QString>
#include <QtGlobal>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper to format baud rates
   */
  class MDT_SERIALPORT_EXPORT BaudRateStringFormat
  {
   public:

    /*! \brief Get a human friendly representation of given baud rate
     *
     * \pre \a rate must be > 0
     * \sa https://en.wikipedia.org/wiki/Serial_port#Settings
     */
    static
    QString toHumanFriendlyString(qint32 rate) noexcept;

    static
    QString toHumanFriendlyString_bps(qint32 rate) noexcept;

    static
    QString toHumanFriendlyString_kbps(qint32 rate) noexcept;

    static
    QString toHumanFriendlyString_Mbps(qint32 rate) noexcept;

    static
    QString number(qint32 n) noexcept;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_BAUD_RATE_STRING_FORMAT_H
