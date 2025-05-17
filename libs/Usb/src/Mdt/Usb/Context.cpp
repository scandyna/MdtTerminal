// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Context.h"
#include "LibusbError.h"
#include <QCoreApplication>
#include <QString>

namespace Mdt{ namespace Usb{

QString contextTr(const char *sourceText) noexcept
{
  return QCoreApplication::translate("Mdt::Usb::Context", sourceText);
}

Context::Context()
{
  int ret = libusb_init(&mContext);
  if(ret != 0){
    const QString msg = contextTr("Construct USB context failed in libusb_init() with code %1: %2")
                        .arg( LibusbError::errorNameFromInt(ret) )
                        .arg( LibusbError::strerrorFromInt(ret) );
    throw LibusbRuntimeError( msg, LibusbError::errorFromInt(ret) );
  }
}

Context::~Context() noexcept
{
  libusb_exit(mContext);
}

}} // namespace Mdt{ namespace Usb{
