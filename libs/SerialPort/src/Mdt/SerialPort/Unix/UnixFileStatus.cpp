// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "UnixFileStatus.h"
#include "Mdt/SerialPort/FilesystemHelpers.h"
#include <QString>
#include <QCoreApplication>
#include <errno.h>
#include <string.h>
#include <cassert>

namespace Mdt{ namespace SerialPort{

QString unixFileStatusTr(const char *sourceText) noexcept
{
  return QCoreApplication::translate("Mdt::SerialPort::UnixFileStatus", sourceText);
}


Unix::FileStatusFileType UnixFileStatus::fileType() const noexcept
{
  const auto type = Unix::fileStatusFileTypeFrom_stat_st_mode(mStat.st_mode);
  /// \todo validation should be done during construction, like in fromStatStruct()
  assert( type.has_value() );

  return *type;
}

UnixFileStatus UnixFileStatus::fromStatStruct(const struct stat & st) noexcept
{
  return UnixFileStatus(st);
}

UnixFileStatus UnixFileStatus::fromPath(const std::filesystem::path & path)
{
  struct stat st;
  int ret = stat(path.native().c_str(), &st);
  if(ret < 0){
    QString msg = unixFileStatusTr("failed to stat %1: %2")
                  .arg( qStringFromStdFilesystemPath(path), QString::fromLocal8Bit( strerror(errno) ) );
    throw FileOpenError(msg);
  }

  return UnixFileStatus(st);
}

UnixFileStatus::UnixFileStatus(const struct stat & st) noexcept
 : mStat(st)
{
}

}} // namespace Mdt{ namespace SerialPort{
