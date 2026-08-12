// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_INTERFACE_STANDARD_H
#define MDT_SERIAL_PORT_INTERFACE_STANDARD_H

namespace Mdt{ namespace SerialPort{

  /*! \brief Interface standard
   *
   * \sa https://en.wikipedia.org/wiki/RS-232
   * \sa https://en.wikipedia.org/wiki/RS-422
   * \sa https://en.wikipedia.org/wiki/RS-485
   */
  enum class InterfaceStandard
  {
    RS_232,     /*!< RS-232 */
    RS_422,     /*!< RS-422 */
    RS_485_2W,  /*!< RS-485 2 wire */
    RS_485_4W,  /*!< RS-485 4 wire */
    System      /*!< Interface handled only by the system,
                     not known to the application.
                     \sa InterfaceList */
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_INTERFACE_STANDARD_H
