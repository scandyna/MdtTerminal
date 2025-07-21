// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PORT_SETUP_ERROR_H
#define MDT_SERIAL_PORT_PORT_SETUP_ERROR_H

#include "Mdt/SerialPort/QRuntimeError.h"
#include "mdt_serialport_export.h"
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Port setup error
   */
  class MDT_SERIALPORT_EXPORT PortSetupError : public QRuntimeError
  {
   public:

    /*! \brief Constructor
     */
    explicit
    PortSetupError(const QString & what)
      : QRuntimeError(what)
    {
    }
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PORT_SETUP_ERROR_H
