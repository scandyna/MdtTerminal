// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PORT_INFO_STRING_FORMAT_H
#define MDT_SERIAL_PORT_PORT_INFO_STRING_FORMAT_H

#include "mdt_serialport_export.h"
#include <QSerialPortInfo>
#include <QObject>
#include <QString>
#include <optional>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper class to get string representation of some port info attributes
   */
  class MDT_SERIALPORT_EXPORT PortInfoStringFormat : public QObject
  {
    Q_OBJECT

   public:

    PortInfoStringFormat(QObject *parent) = delete;

    /*! \brief Returns the string representation of given vendor identifier
     *
     * Returns an empty string if \a vid has no value
     */
    static
    QString vendorIdentifierToString(std::optional<quint16> vid) noexcept;

    /*! \brief Returns the string representation of the vendor identifier
     *
     * Returns an empty string if \a portInfo has no vendor identifier
     */
    static
    QString vendorIdentifierToString(const QSerialPortInfo & portInfo) noexcept;

    /*! \brief Returns the string representation of given product identifier
     *
     * Returns an empty string if \a pid has no value
     */
    static
    QString productIdentifierToString(std::optional<quint16> pid) noexcept;

    /*! \brief Returns the string representation of the product identifier
     *
     * Returns an empty string if \a portInfo has no product identifier
     */
    static
    QString productIdentifierToString(const QSerialPortInfo & portInfo) noexcept;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PORT_INFO_STRING_FORMAT_H
