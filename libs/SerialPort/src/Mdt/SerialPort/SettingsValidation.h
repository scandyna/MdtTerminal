// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_VALIDATION_H
#define MDT_SERIAL_PORT_SETTINGS_VALIDATION_H

#include "Mdt/SerialPort/SettingsRawData.h"
#include "Mdt/SerialPort/SettingsValidationError.h"
#include "mdt_serialport_export.h"
#include <QObject>
#include <QString>

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

    /*! \brief Validate stop bits
     *
     * \exception SettingsValidationError
     * \sa Settings::stopBitsHasMinimalValidity()
     */
    static
    void validateStopBits(QSerialPort::StopBits bits);

    /*! \brief Validate send byte by byte settings
     *
     * The \a intervalInMilliseconds has only meaning if \a enable is true.
     *
     * \exception SettingsValidationError
     * \sa SendByteByByteSettings::rawIntervalInMillisecondsIsValid()
     */
    static
    void validateSendByteByByteSettings(bool enable, int intervalInMilliseconds);
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_VALIDATION_H
