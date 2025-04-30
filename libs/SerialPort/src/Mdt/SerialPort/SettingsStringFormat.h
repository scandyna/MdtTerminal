// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_STRING_FORMAT_H
#define MDT_SERIAL_PORT_SETTINGS_STRING_FORMAT_H

#include "Mdt/SerialPort/Settings.h"
#include "mdt_serialport_export.h"
#include <QSerialPort>
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper class for string formatting of settings
   */
  class MDT_SERIALPORT_EXPORT SettingsStringFormat
  {
   public:

    /*! \brief Get the baud rate - data bits - parity - stop bits notation string from given settings
     *
     * Returns a string in the D-P-S notation:
     * - D: data bits
     * - P: parity
     * - S: stop bits
     *
     * Example: 8-N-1
     *
     * \sa https://en.wikipedia.org/wiki/Serial_port#Conventional_notation
     */
    static
    QString dpsStringFromSettings(const Settings & settings) noexcept;

    /*! \brief Get the baud rate - data bits - parity - stop bits notation string from given port
     *
     * \sa dpsStringFromSettings()
     */
    static
    QString dpsStringFromPort(const QSerialPort & port) noexcept;

    /*! \brief Get the baud rate - data bits - parity - stop bits from given settings
     *
     * \sa dpsStringFromSettings()
     * \sa https://en.wikipedia.org/wiki/Serial_port#Conventional_notation
     */
    static
    QString baudeRateAndDpsStringFromSettings(const Settings & settings) noexcept;

    /*! \brief Get the baud rate - data bits - parity - stop bits from given port
     *
     * \sa baudeRateAndDpsStringFromSettings()
     */
    static
    QString baudeRateAndDpsStringFromPort(const QSerialPort & port) noexcept;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_STRING_FORMAT_H
