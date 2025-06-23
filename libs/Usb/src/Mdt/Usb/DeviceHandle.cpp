// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "DeviceHandle.h"
#include "LibusbError.h"
#include <QCoreApplication>
#include <QString>
#include <cassert>

namespace Mdt{ namespace Usb{

QString DeviceHandleTr(const char *sourceText) noexcept
{
  return QCoreApplication::translate("Mdt::Usb::DeviceHandle", sourceText);
}


DeviceHandle::~DeviceHandle() noexcept
{
  libusb_close(mHandle);
}

DeviceHandle DeviceHandle::open(libusb_device *device)
{
  assert(device != nullptr);

  libusb_device_handle *handle = nullptr;
  int ret = libusb_open(device, &handle);
  if(ret != 0){
    const QString msg = DeviceHandleTr("open USB device failed with code %1: %2")
                        .arg( LibusbError::errorNameFromInt(ret) )
                        .arg( LibusbError::strerrorFromInt(ret) );
    throw LibusbRuntimeError( msg, LibusbError::errorFromInt(ret) );
  }

  return DeviceHandle(handle);
}

DeviceHandle::DeviceHandle(libusb_device_handle *handle) noexcept
 : mHandle(handle)
{
  assert(mHandle != nullptr);
}

}} // namespace Mdt{ namespace Usb{
