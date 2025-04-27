// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PORT_SETUP_H
#define MDT_SERIAL_PORT_PORT_SETUP_H

#include "Mdt/SerialPort/Settings.h"
#include "mdt_serialport_export.h"
#include <QSerialPort>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper to set settings to a serial port
   *
   * \todo Should getting/setting some HW settings,
   * like interface, be done here ?
   * This would require to do a basic open..
   */
  class MDT_SERIALPORT_EXPORT PortSetup
  {
   public:

    /*! \brief Set given settings to given port
     *
     * \pre \a port must not be open
     */
    static
    void setSettingsToPort(const Settings & settings, QSerialPort & port);

    /*! \brief Get settings from given port
     */
    static
    Settings getSettingsFromPort(const QSerialPort & port);
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PORT_SETUP_H
