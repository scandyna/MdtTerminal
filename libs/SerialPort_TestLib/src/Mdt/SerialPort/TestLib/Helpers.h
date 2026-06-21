// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_TEST_LIB_HELPERS_H
#define MDT_SERIAL_PORT_TEST_LIB_HELPERS_H

#include "Mdt/SerialPort/PortInfo.h"
#include "mdt_serialport_testlib_export.h"
#include <QSerialPort>
#include <QString>
#include <optional>

namespace Mdt{ namespace SerialPort{ namespace TestLib{

  /*! \brief Find the first available serial port
   *
   * This function also works around some issues,
   * like https://gitlab.com/scandyna/mdtterminal/-/work_items/9
   */
  MDT_SERIALPORT_TESTLIB_EXPORT
  std::optional<PortInfo> findFirstAvailableSerialPort();

  /*! \brief Open the first available serial port
   *
   * This function also works around some issues,
   * like https://gitlab.com/scandyna/mdtterminal/-/work_items/9
   *
   * \pre \a serialPort must not be open
   */
  MDT_SERIALPORT_TESTLIB_EXPORT
  bool openFirstAvailableSerialPort(QSerialPort & serialPort, QSerialPort::OpenMode openMode);

  /*! \brief Get the name of the serial port with the bridge plug attached
   *
   * This function excepts an environment variable,
   * named `MDT_SERIALPORT_TEST_PORT_NAME_WITH_BRIDGE_PLUG`.
   *
   * This variable must be set to the port name, like ttyS0 or COM1.
   *
   * Example on %Linux:
   * \code
   * export MDT_SERIALPORT_TEST_PORT_NAME_WITH_BRIDGE_PLUG="ttyS0"
   * \endcode
   *
   * \sa \ref SerialPort_Testing_WithBridgePlug
   */
  MDT_SERIALPORT_TESTLIB_EXPORT
  QString serialPortNameWithBridgePlug();

  /*! \brief Find the serial port with the bridge plug attached
   *
   * \sa serialPortNameWithBridgePlug()
   */
  MDT_SERIALPORT_TESTLIB_EXPORT
  std::optional<PortInfo> findSerialPortWithBridgePlug();

  /*! \brief Open the serial port with the bridge plug attached
   *
   * \pre \a serialPort must not be open
   * \sa serialPortNameWithBridgePlug()
   */
  MDT_SERIALPORT_TESTLIB_EXPORT
  bool openSerialPortWithBridgePlug(QSerialPort & serialPort);

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{

#endif // #ifndef MDT_SERIAL_PORT_TEST_LIB_HELPERS_H
