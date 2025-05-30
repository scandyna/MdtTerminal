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

namespace Mdt{ namespace SerialPort{

UnixFileStatus UnixFileStatus::fromStatStruct(const struct stat & st) noexcept
{
  return UnixFileStatus(st);
}

UnixFileStatus::UnixFileStatus(const struct stat & st) noexcept
 : mStat(st)
{
}

}} // namespace Mdt{ namespace SerialPort{
