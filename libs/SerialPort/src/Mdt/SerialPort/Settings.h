// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_H
#define MDT_SERIAL_PORT_SETTINGS_H

#include "mdt_serialport_export.h"
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Serial port settings
   */
  class MDT_SERIALPORT_EXPORT Settings
  {
   public:

    /*! \brief Set the port name
     */
    void setPortName(const QString & name) noexcept;

    /*! \brief Get the port name
     */
    const QString & portName() const noexcept
    {
      return mPortName;
    }

   private:

    QString mPortName;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_H
