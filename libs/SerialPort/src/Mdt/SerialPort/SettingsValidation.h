// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_VALIDATION_H
#define MDT_SERIAL_PORT_SETTINGS_VALIDATION_H

#include "Mdt/SerialPort/SettingsRawData.h"
#include "Mdt/SerialPort/SettingsValidationError.h"
#include "mdt_serialport_export.h"
#include <QObject>

namespace Mdt{ namespace SerialPort{

  /*! \brief Offers some minimal validation to create settings
   */
  class MDT_SERIALPORT_EXPORT SettingsValidation : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Validate given settings
     *
     * \exception SettingsValidationError
     */
    static
    void validateSettings(const SettingsRawData & data);

    /*! \brief Validate given baud rate
     *
     * \exception SettingsValidationError
     */
    static
    void validateBaudRate(qint32 rate);

    /*! \brief Validate data bits
     *
     * \exception SettingsValidationError
     */
    static
    void validateDataBits(QSerialPort::DataBits bits);

    /*! \brief Validate parity
     *
     * \exception SettingsValidationError
     */
    static
    void validateParity(QSerialPort::Parity parity);

    /*! \brief Validate flow control
     *
     * \exception SettingsValidationError
     */
    static
    void validateFlowControl(QSerialPort::FlowControl control);
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_VALIDATION_H
