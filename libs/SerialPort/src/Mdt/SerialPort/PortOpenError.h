// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PORT_OPEN_ERROR_H
#define MDT_SERIAL_PORT_PORT_OPEN_ERROR_H

#include "Mdt/SerialPort/QRuntimeError.h"
#include "mdt_serialport_export.h"
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Port open error
   */
  class MDT_SERIALPORT_EXPORT PortOpenError : public QRuntimeError
  {
   public:

    /*! \brief Constructor
     */
    explicit
    PortOpenError(const QString & what)
      : QRuntimeError(what)
    {
    }
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PORT_OPEN_ERROR_H
