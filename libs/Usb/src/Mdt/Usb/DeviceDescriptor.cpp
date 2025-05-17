// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "DeviceDescriptor.h"
#include <cassert>

namespace Mdt{ namespace Usb{

DeviceDescriptor DeviceDescriptor::fromLibusbDevicePointer(libusb_device *device) noexcept
{
  assert(device != nullptr);

  
}

}} // namespace Mdt{ namespace Usb{
