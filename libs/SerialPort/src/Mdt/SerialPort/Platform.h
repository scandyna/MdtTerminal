// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PLATFORM_H
#define MDT_SERIAL_PORT_PLATFORM_H

// #include "mdt_serialport_export.h"
#include <QtGlobal>
// #include <QtSystemDetection> Qt6

namespace Mdt{ namespace SerialPort{

  /*! \brief Returns true when building for Windows
   */
  constexpr
  bool osIsWindows() noexcept
  {
#if Q_OS_WINN
    return true;
#else
    return false;
#endif
  }

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PLATFORM_H
