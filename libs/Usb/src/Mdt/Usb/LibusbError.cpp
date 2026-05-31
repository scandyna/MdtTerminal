// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "LibusbError.h"

namespace Mdt{ namespace Usb{

QString LibusbError::errorName(libusb_error code) noexcept
{
  assert(code <= 0);
  /*
   * libusb_error_name() return ASCII
   * We must not free returned pointer
   */
  return QString::fromLatin1( libusb_error_name(code) );
}

}} // namespace Mdt{ namespace Usb{
