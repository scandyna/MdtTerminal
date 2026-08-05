// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_LINUX_MOXA_UPORT_H
#define MDT_SERIAL_PORT_LINUX_MOXA_UPORT_H

#include "mdt_serialport_export.h"
#include <string>

namespace Mdt{ namespace SerialPort{ namespace Linux{

  // class MDT_SERIALPORT_EXPORT MoxaUPort
  // {
  // };

  /*! \page SerialPort_Linux_MoxaUPort Moxa UPort on %Linux specifics
   *
   * \sa \ref SerialPort_Device_MoxaUPort
   * \section SerialPort_Linux_MoxaUPort_ModuleFunctions Moxa UPort on Linux module functions
   *
   * This module provides thoses functions:
   * - isLinuxMxuportDriver()
   * - isMoxaMxuportDriver()
   *
   * \sa \ref SerialPort_Device_MoxaUPort
   *
   *
   * \subsection SerialPort_Linux_MoxaUPort_ConfigureMoxaUportInterfaceLinux Configure a Moxa Uport interface on Linux
   *
   * A way to configure the interface is to use serial_struct.
   * The port field of this struct corresponds to the interface (parameter value).
   * The TIOCSSERIAL ioctl can then be used to configure the interface on the device.
   * ioctl() works on a file handle. This means that the port must be open.
   *
   * Sadly, the the official %Linux driver, mxuport,
   * does not implement the TIOCGSERIAL and TIOCSSERIAL ioctl's.
   *
   * The %Linux drivers provided by Moxa implement those.
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
   * Looking around the official %Linux driver, mxuport.c,
   * and also the Moxa provided one, I could not find how to get this interface.
   *
   * The official %Linux driver sets the RS-232 interface in mxuport_port_probe()
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
   * If we use the official %Linux driver, we have to set the interface
   * with an USB call before open port.
   *
   * If we use the Moxa provided driver,
   * we have to use the TIOCGSERIAL and TIOCSSERIAL ioctl's,
   * once the port is open.
   *
   * \subsubsection SerialPort_Linux_MoxaUPort_DifferiencateDriverWithUdev Differenciate between Linux native and Moxa provided driver
   *
   * Using Udevadm we can see the tree:
   * \code
   * udevadm info -a /dev/ttyUSB0
   * \endcode
   *
   * Top of the result with the native %Linux driver:
   * \code
   * looking at device '/devices/pci0000:00/0000:00:1a.0/usb1/1-1/1-1.4/1-1.4:1.0/ttyUSB0/tty/ttyUSB0':
   *   KERNEL=="ttyUSB0"
   *   SUBSYSTEM=="tty"
   *   DRIVER==""
   *
   * looking at parent device '/devices/pci0000:00/0000:00:1a.0/usb1/1-1/1-1.4/1-1.4:1.0/ttyUSB0':
   *   KERNELS=="ttyUSB0"
   *   SUBSYSTEMS=="usb-serial"
   *   DRIVERS=="mxuport"
   *   A*TTRS{port_number}=="0"
   *
   * looking at parent device '/devices/pci0000:00/0000:00:1a.0/usb1/1-1/1-1.4/1-1.4:1.0':
   *   KERNELS=="1-1.4:1.0"
   *   SUBSYSTEMS=="usb"
   *   DRIVERS=="mxuport"
   *   ...
   * \endcode
   *
   * Here with the Moxa driver:
   * \code
   * looking at device '/devices/pci0000:00/0000:00:0b.0/usb1/1-1/1-1:1.0/ttyMXUSB0/tty/ttyMXUSB0':
   *   KERNEL=="ttyMXUSB0"
   *   SUBSYSTEM=="tty"
   *   DRIVER==""
   *
   * looking at parent device '/devices/pci0000:00/0000:00:0b.0/usb1/1-1/1-1:1.0/ttyMXUSB0':
   *   KERNELS=="ttyMXUSB0"
   *   SUBSYSTEMS=="mxusb-serial"
   *   DRIVERS=="MxUPort-2P"
   *   ATTRS{port_number}=="0"
   *
   * looking at parent device '/devices/pci0000:00/0000:00:0b.0/usb1/1-1/1-1:1.0':
   *   KERNELS=="1-1:1.0"
   *   SUBSYSTEMS=="usb"
   *   DRIVERS=="mxuport"
   * \endcode
   *
   * \sa UdevUsbSerialPort
   */

  /*! \brief Check if given driver name represents a %Linux UPort driver
   */
  MDT_SERIALPORT_EXPORT
  bool isLinuxMxuportDriver(const std::string & driverName) noexcept;

  /*! \brief Check if given driver name represents a %Linux UPort driver
   */
  MDT_SERIALPORT_EXPORT
  bool isMoxaMxuportDriver(const std::string & driverName) noexcept;

}}} // namespace Mdt{ namespace SerialPort{ namespace Linux{

#endif // #ifndef MDT_SERIAL_PORT_LINUX_MOXA_UPORT_H
