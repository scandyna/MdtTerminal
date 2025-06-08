// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_UNIX_FILE_STATUS_FILE_TYPE_H
#define MDT_SERIAL_PORT_UNIX_FILE_STATUS_FILE_TYPE_H

#include "mdt_serialport_export.h"
#include <sys/stat.h>
#include <optional>

namespace Mdt{ namespace SerialPort{ namespace Unix{

  /*! \brief File status file type (type field of stat.st_mode)
   *
   * \sa https://man7.org/linux/man-pages/man7/inode.7.html
   */
  enum class FileStatusFileType
  {
    RegularFile,
    Directory,
    CharacterDevice,
    BlockDevice,
    Fifo,
    SymbolicLink,
    Socket
  };

  /*! \brief Get the file type from given status mode (stat.st_mode)
   *
   * \sa https://man7.org/linux/man-pages/man7/inode.7.html
   */
  MDT_SERIALPORT_EXPORT
  std::optional<FileStatusFileType> fileStatusFileTypeFrom_stat_st_mode(mode_t st_mode) noexcept;

}}} // namespace Mdt{ namespace SerialPort{ namespace Unix{

#endif // #ifndef MDT_SERIAL_PORT_UNIX_FILE_STATUS_FILE_TYPE_H
