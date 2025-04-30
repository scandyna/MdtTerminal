// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_FLOW_CONTROL_STRING_FORMAT_H
#define MDT_SERIAL_PORT_FLOW_CONTROL_STRING_FORMAT_H

#include "mdt_serialport_export.h"
#include <QSerialPort>
#include <QObject>
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper class to get a translated string representation of a flow control
   *
   * \sa https://en.wikipedia.org/wiki/Serial_port#Flow_control
   * \sa https://doc.qt.io/qt-6/qserialport.html#FlowControl-enum
   */
  class MDT_SERIALPORT_EXPORT FlowControlStringFormat : public QObject
  {
    Q_OBJECT

   public:

    FlowControlStringFormat(QObject *parent) = delete;

    /*! \brief Get the string representation of given flow control
     *
     * \note Returns a user friendly translated string
     */
    static
    QString flowControlToString(QSerialPort::FlowControl control) noexcept;

    /*! \brief Get a short string representation of given flow control
     */
    static
    QString flowControlToShortString(QSerialPort::FlowControl control) noexcept;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_FLOW_CONTROL_STRING_FORMAT_H
