// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_VALIDATION_ERROR_H
#define MDT_SERIAL_PORT_SETTINGS_VALIDATION_ERROR_H

#include "Mdt/SerialPort/QRuntimeError.h"
#include "mdt_serialport_export.h"
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Error thrown when a settings validation occurs
   */
  class MDT_SERIALPORT_EXPORT SettingsValidationError : public QRuntimeError
  {
   public:

    /*! \brief Construct an error
     */
    explicit
    SettingsValidationError(const QString & text)
     : QRuntimeError(text)
    {
    }
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_VALIDATION_ERROR_H
