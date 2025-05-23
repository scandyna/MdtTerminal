// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "ConfigDescriptor.h"
#include "LibusbError.h"
#include <QCoreApplication>
#include <QString>
#include <cassert>

namespace Mdt{ namespace Usb{

QString configDescriptorTr(const char *sourceText) noexcept
{
  return QCoreApplication::translate("Mdt::Usb::ConfigDescriptor", sourceText);
}


ConfigDescriptor ConfigDescriptor::fromLibusbDescriptor(const libusb_config_descriptor & descriptor) noexcept
{
  return ConfigDescriptor(descriptor);
}

ConfigDescriptor ConfigDescriptor::activeConfigFromLibusbDevicePointer(libusb_device *device)
{
  assert(device != nullptr);

  libusb_config_descriptor *libusbDescriptor;
  int ret = libusb_get_active_config_descriptor(device, &libusbDescriptor);
  if(ret != 0){
    const QString msg = configDescriptorTr("Get active configuration failed in libusb_get_active_config_descriptor() with code %1: %2")
                        .arg( LibusbError::errorNameFromInt(ret) )
                        .arg( LibusbError::strerrorFromInt(ret) );
    libusb_free_config_descriptor(libusbDescriptor);
    throw LibusbRuntimeError( msg, LibusbError::errorFromInt(ret) );
  }

  ConfigDescriptor descriptor = fromLibusbDescriptor(*libusbDescriptor);
  libusb_free_config_descriptor(libusbDescriptor);

  return descriptor;
}

}} // namespace Mdt{ namespace Usb{
