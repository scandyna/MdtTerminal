// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_FILESYSTEM_HELPERS_H
#define MDT_SERIAL_PORT_FILESYSTEM_HELPERS_H

#include "mdt_serialport_export.h"
#include <QString>
#include <filesystem>

namespace Mdt{ namespace SerialPort{

  /*! \brief Get the QString representation from given path
   */
  MDT_SERIALPORT_EXPORT
  QString qStringFromStdFilesystemPath(const std::filesystem::path & path) noexcept;

  /*! \brief Get a path from given QString
   */
  MDT_SERIALPORT_EXPORT
  std::filesystem::path stdFilesystemPathFromQString(const QString & path) noexcept;

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_FILESYSTEM_HELPERS_H
