// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_INTERFACE_STRING_FORMAT_H
#define MDT_SERIAL_PORT_INTERFACE_STRING_FORMAT_H

#include "Mdt/SerialPort/InterfaceStandard.h"
#include "mdt_serialport_export.h"
#include <QObject>
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper class to get string representation of a serial port adapter interface
   */
  class MDT_SERIALPORT_EXPORT InterfaceStringFormat : public QObject
  {
    Q_OBJECT

   public:

    InterfaceStringFormat(QObject *parent) = delete;

    /*! \brief Get the name for given standard
     */
    static
    QString standardName(InterfaceStandard standard) noexcept;

    /*! \brief Get the RS-232 name
     */
    static
    QString rs232Name() noexcept;

    /*! \brief Get the RS-422 name
     */
    static
    QString rs422Name() noexcept;

    /*! \brief Get the RS-485 2 wire name
     */
    static
    QString rs485TwoWireName() noexcept;

    /*! \brief Get the RS-485 4 wire name
     */
    static
    QString rs485FourWireName() noexcept;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_INTERFACE_STRING_FORMAT_H
