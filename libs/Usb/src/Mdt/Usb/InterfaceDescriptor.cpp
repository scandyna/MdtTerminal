// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "InterfaceDescriptor.h"

namespace Mdt{ namespace Usb{

InterfaceDescriptor InterfaceDescriptor::fromLibusbDescriptor(const libusb_interface_descriptor & descriptor) noexcept
{
  InterfaceDescriptor interface;
  interface.mbNumEndpoints = descriptor.bNumEndpoints;

  return interface;
}

}} // namespace Mdt{ namespace Usb{
