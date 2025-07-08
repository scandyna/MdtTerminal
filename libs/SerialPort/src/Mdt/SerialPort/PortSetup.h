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
#include "Mdt/SerialPort/Interface.h"
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

    /*! \brief Configure the interface of a Moxa Uport on Linux
     *
     * A way to configure the interface is to use serial_struct.
     * The port field of this struct corresponds to the interface (parameter value).
     * The TIOCSSERIAL ioctl can then be used to configure the interface on the device.
     * ioctl() works on a file handle. This means that the port must be open.
     *
     * Sadly, the the official Linux driver, mxuport,
     * does not implement the TIOCGSERIAL and TIOCSSERIAL ioctl's.
     *
     * The Linux drivers provided by Moxa implement those.
     *
     * It's possible to configure the interface with an USB control call from user space.
     * The port should not be open during this step.
     *
     * USB calls from user space also requires some permissions.
     * For this, udev rules can be added.
     * Example on an Ubuntu:
     * \code
     * # /etc/udev/rules.d/55-usb-moxauport.rules
     * SUBSYSTEM=="usb", ATTR{idVendor}=="110a", ATTRS{idProduct}=="1250", GROUP="plugdev", MODE="0660"
     * \endcode
     *
     * Query the device about current interface seems not possible.
     * Looking around the official Linux driver, mxuport.c,
     * and also the Moxa provided one, I could not find how to get this interface.
     *
     * The official Linux driver sets the RS-232 interface in mxuport_port_probe()
     * (with an USB control call).
     * This means, when the device is plugged (or the system starts),
     * the RS-232 interface is set.
     * By open port, theire is no USB call to set the interface.
     *
     * The Moxa driver sets the interface in mx_init_port() (with an USB control call),
     * called by mxuport_open(), to the requested interface.
     * The requested interface is probably related with the serial_struct's port member.
     * In mxuport_port_probe(), the requested interface is defined to RS-232.
     * This means, by open port, the interface is set.
     *
     * Summary
     *
     * If we use the official Linux driver, we have to set the interface
     * with an USB call before open port.
     *
     * If we use the Moxa provided driver,
     * we have to use the TIOCGSERIAL and TIOCSSERIAL ioctl's,
     * once the port is open.
     *
     * 
     *
     * \todo is it possible to query what driver is installed ?
     *
     * configureBeforeOpen()
     * consfigureOnceOpen()
     *
     * OR simply
     *
     * openPort() helper that does all ? hmm.. not here..
     */

    /*! \brief Configure the interface for given port
     *
     * \exception PortSetupError
     * \pre \a port must be open
     */
    static
    void configureInterface(const Interface & interface, QSerialPort & port);

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
