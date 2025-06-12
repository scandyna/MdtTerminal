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
#include "DeviceDescriptor.h"

namespace Mdt{ namespace Usb{

LibusbDeviceList::~LibusbDeviceList() noexcept
{
  libusb_free_device_list(mList, 1);
}

libusb_device *LibusbDeviceList::findFirstLibusbDeviceWithVidAndPid(uint16_t vid, uint16_t pid) const noexcept
{
  for(size_t i=0; i < count(); ++i){
    libusb_device *device = libusbDevicePointerAt(i);
    const auto deviceDescriptor = DeviceDescriptor::fromLibusbDevicePointer(device);
    if( (deviceDescriptor.idVendor() == vid) && (deviceDescriptor.idProduct() == pid) ){
      return device;
    }
  }

  return nullptr;
}

libusb_device *LibusbDeviceList::findLibusbDeviceOnBusWithAddress(uint8_t busNumber, uint8_t deviceAddress) const noexcept
{
  for(size_t i=0; i < count(); ++i){
    libusb_device *device = libusbDevicePointerAt(i);
    if( (libusb_get_bus_number(device) == busNumber) && (libusb_get_device_address(device) == deviceAddress) ){
      return device;
    }
  }

  return nullptr;
}

}} // namespace Mdt{ namespace Usb{
