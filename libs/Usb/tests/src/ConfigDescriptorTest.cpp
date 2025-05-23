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
  /// \tod maybe an array of libusb_interface ?

  libusb_interface_descriptor defaultLibusbInterface;
  defaultLibusbInterface.bNumEndpoints = 1;

  libusb_interface_descriptor libusbInterfaceList[1]
  {
    defaultLibusbInterface
  };

  libusb_interface libusbInterfaceAltSetting;
  libusbInterfaceAltSetting.altsetting = libusbInterfaceList;
  libusbInterfaceAltSetting.num_altsetting = 1;

  libusb_interface libusbInterfaceAltSettingList[1]
  {
    libusbInterfaceAltSetting
  };

  libusb_config_descriptor libusbConfig;
  libusbConfig.interface = libusbInterfaceAltSettingList;
  libusbConfig.bNumInterfaces = 1;

  const auto descriptor = ConfigDescriptor::fromLibusbDescriptor(libusbConfig);

  CHECK( descriptor.bNumInterfaces() == 1 );
  
}
