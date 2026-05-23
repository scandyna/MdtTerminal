// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Handle.h"

namespace Mdt{ namespace SerialPort{

bool Handle::nativeHandleIsNull(NativeHandle h) noexcept
{
  /// \todo check if correct
  return h < 0;
}

Handle Handle::fromNativeHandle(int h)
{
  return Handle(h);
}

}} // namespace Mdt{ namespace SerialPort{
