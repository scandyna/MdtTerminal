// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Interface.h"
#include <cassert>

namespace Mdt{ namespace Usb{

Interface Interface::fromLibusbInterface(const libusb_interface & interface) noexcept
{
  assert(interface.altsetting != nullptr);

  Interface alternateSettings;

  for(int i=0; i < interface.num_altsetting; ++i){
    alternateSettings.mAlternateSettings.push_back( InterfaceDescriptor::fromLibusbDescriptor(interface.altsetting[i]) );
  }

  return alternateSettings;
}

}} // namespace Mdt{ namespace Usb{
