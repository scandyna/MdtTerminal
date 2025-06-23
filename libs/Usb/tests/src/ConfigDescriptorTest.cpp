// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/ConfigDescriptor.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("fromLibusbDescriptor")
{
  libusb_interface_descriptor defaultLibusbInterface;
  defaultLibusbInterface.bNumEndpoints = 0;

  libusb_interface_descriptor libusbInterfaceAltSettingList[1]
  {
    defaultLibusbInterface
  };

  libusb_interface libusbInterface;
  libusbInterface.altsetting = libusbInterfaceAltSettingList;
  libusbInterface.num_altsetting = 1;

  libusb_interface libusbInterfaceList[1]
  {
    libusbInterface
  };

  libusb_config_descriptor libusbConfig;
  libusbConfig.interface = libusbInterfaceList;
  libusbConfig.bNumInterfaces = 1;

  const auto descriptor = ConfigDescriptor::fromLibusbDescriptor(libusbConfig);

  CHECK( descriptor.interfaceCount() == 1 );
  CHECK( descriptor.bNumInterfaces() == 1 );
  CHECK( descriptor.interfaceAt(0).alternateSettingsCount() == 1 );
}
