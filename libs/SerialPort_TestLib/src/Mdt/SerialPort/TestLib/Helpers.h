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

#include "mdt_serialport_testlib_export.h"
#include <QSerialPort>

namespace Mdt{ namespace SerialPort{ namespace TestLib{

  /*! \brief Open the first available serial port
   *
   * This function also works around some issues,
   * like https://gitlab.com/scandyna/mdtterminal/-/work_items/9
   *
   * \pre \a serialPort must not be open
   */
  MDT_SERIALPORT_TESTLIB_EXPORT
  bool openFirstAvailableSerialPort(QSerialPort & serialPort, QSerialPort::OpenMode openMode);

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{

#endif // #ifndef MDT_SERIAL_PORT_TEST_LIB_HELPERS_H
