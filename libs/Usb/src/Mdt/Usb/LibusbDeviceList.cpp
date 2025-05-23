// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "LibusbDeviceList.h"

namespace Mdt{ namespace Usb{

LibusbDeviceList::~LibusbDeviceList() noexcept
{
  libusb_free_device_list(mList, 1);
}

}} // namespace Mdt{ namespace Usb{
