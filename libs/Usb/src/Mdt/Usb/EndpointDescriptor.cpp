// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "EndpointDescriptor.h"

namespace Mdt{ namespace Usb{

EndpointDescriptor EndpointDescriptor::fromLibusbDescriptor(const libusb_endpoint_descriptor & descriptor) noexcept
{
  EndpointDescriptor endpoint;
  endpoint.mbEndpointAddress = descriptor.bEndpointAddress;

  return endpoint;
}

}} // namespace Mdt{ namespace Usb{
