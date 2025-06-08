// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "FileStatusFileType.h"

namespace Mdt{ namespace SerialPort{ namespace Unix{

std::optional<FileStatusFileType> fileStatusFileTypeFrom_stat_st_mode(mode_t st_mode) noexcept
{
  if( S_ISREG(st_mode) ){
    return FileStatusFileType::RegularFile;
  }
  if( S_ISDIR(st_mode) ){
    return FileStatusFileType::Directory;
  }
  if( S_ISCHR(st_mode) ){
    return FileStatusFileType::CharacterDevice;
  }
  if( S_ISBLK(st_mode) ){
    return FileStatusFileType::BlockDevice;
  }
  if( S_ISFIFO(st_mode) ){
    return FileStatusFileType::Fifo;
  }
  if( S_ISLNK(st_mode) ){
    return FileStatusFileType::SymbolicLink;
  }
  if( S_ISSOCK(st_mode) ){
    return FileStatusFileType::Socket;
  }

  return {};
}

}}} // namespace Mdt{ namespace SerialPort{ namespace Unix{
