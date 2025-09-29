// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "AbstractWriter.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

AbstractWriter::AbstractWriter(QIODevice *device, QObject *parent)
 : QObject(parent),
   mDevice(device)
{
  assert( !mDevice.isNull() );

  connect(mDevice, &QIODevice::aboutToClose, this, &AbstractWriter::clear);
}

}} // namespace Mdt{ namespace SerialPort{
