// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "DeviceEnumerator.h"
#include "LibusbError.h"
#include <libusb.h>
#include <cassert>

namespace Mdt{ namespace Usb{

DeviceEnumerator::DeviceEnumerator(std::shared_ptr<Context> context, QObject *parent)
  : QObject(parent),
    mContext(context)
{
  assert(context != nullptr);
}

LibusbDeviceList DeviceEnumerator::scanForAttachedDevices()
{
  assert(mContext != nullptr);

  LibusbDeviceList list;

  ssize_t cnt = libusb_get_device_list(mContext->libusbContext(), &list.mList);
  if(cnt < 0){
    const QString msg = tr("Scan for attached devices failed in libusb_get_device_list() with code %1: %2")
                        .arg( LibusbError::errorNameFrom_ssize_t(cnt) )
                        .arg( LibusbError::strerrorFrom_ssize_t(cnt) );
    throw LibusbRuntimeError( msg, LibusbError::errorFrom_ssize_t(cnt) );
  }

  assert(cnt >= 0);
  list.mCount = static_cast<size_t>(cnt);

  return list;
}

}} // namespace Mdt{ namespace Usb{
