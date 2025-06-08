// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Unix/FileStatusFileType.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::Unix;

/*
  S_IFSOCK   0140000   socket
  S_IFLNK    0120000   symbolic link
  S_IFREG    0100000   regular file
  S_IFBLK    0060000   block device
  S_IFDIR    0040000   directory
  S_IFCHR    0020000   character device
  S_IFIFO    0010000   FIFO
*/
TEST_CASE("fileStatusFileTypeFrom_stat_st_mode")
{
  CHECK( !fileStatusFileTypeFrom_stat_st_mode(0000012).has_value() );
  CHECK( fileStatusFileTypeFrom_stat_st_mode(0140000).has_value() );
  CHECK( *fileStatusFileTypeFrom_stat_st_mode(0140000) == FileStatusFileType::Socket );
  CHECK( *fileStatusFileTypeFrom_stat_st_mode(0120000) == FileStatusFileType::SymbolicLink );
  CHECK( *fileStatusFileTypeFrom_stat_st_mode(0100000) == FileStatusFileType::RegularFile );
  CHECK( *fileStatusFileTypeFrom_stat_st_mode(0060000) == FileStatusFileType::BlockDevice );
  CHECK( *fileStatusFileTypeFrom_stat_st_mode(0040000) == FileStatusFileType::Directory );
  CHECK( *fileStatusFileTypeFrom_stat_st_mode(0020000) == FileStatusFileType::CharacterDevice );
  CHECK( *fileStatusFileTypeFrom_stat_st_mode(0010000) == FileStatusFileType::Fifo );
}
