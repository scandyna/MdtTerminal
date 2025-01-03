// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PARITY_STRING_FORMAT_H
#define MDT_SERIAL_PORT_PARITY_STRING_FORMAT_H

#include "mdt_serialport_export.h"
#include <QSerialPort>
#include <QObject>
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper class to get a translated string representation of a parity
   */
  class MDT_SERIALPORT_EXPORT ParityStringFormat : public QObject
  {
    Q_OBJECT

   public:

    ParityStringFormat(QObject *parent) = delete;

    /*! \brief Get the string representation of given parity
     */
    static
    QString parityToString(QSerialPort::Parity parity) noexcept;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PARITY_STRING_FORMAT_H
