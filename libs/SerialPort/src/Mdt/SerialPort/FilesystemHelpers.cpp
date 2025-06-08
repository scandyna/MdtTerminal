// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "FilesystemHelpers.h"
#include <QtGlobal>

namespace Mdt{ namespace SerialPort{

QString qStringFromStdFilesystemPath(const std::filesystem::path & path) noexcept
{
  /*
   * Implementation found in qfile.h
   * for Qt 6.2.3
   */
#ifdef Q_OS_WIN
  return QString::fromStdWString( path.native() );
#else
  return QString::fromStdString( path.native() );
#endif
}

std::filesystem::path stdFilesystemPathFromQString(const QString & path) noexcept
{
#ifdef Q_OS_WIN
  return std::filesystem::path( path.toStdWString() );
#else
  return std::filesystem::path( path.toStdString() );
#endif
}

}} // namespace Mdt{ namespace SerialPort{
