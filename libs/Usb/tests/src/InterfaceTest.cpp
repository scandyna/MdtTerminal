// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/Interface.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("fromLibusbInterface")
{
  libusb_interface_descriptor defaultLibusbInterface;
  defaultLibusbInterface.bNumEndpoints = 1;

  libusb_interface_descriptor libusbInterfaceList[1]
  {
    defaultLibusbInterface
  };

  libusb_interface libusbInterface;
  libusbInterface.altsetting = libusbInterfaceList;
  libusbInterface.num_altsetting = 1;

  const auto interface = Interface::fromLibusbInterface(libusbInterface);

  CHECK( interface.alternateSettingsCount() == 1 );
  CHECK( interface.alternateSettingAt(0).bNumEndpoints() == 1 );
}
