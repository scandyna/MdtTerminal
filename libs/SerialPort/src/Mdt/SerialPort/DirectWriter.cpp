// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "DirectWriter.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

DirectWriter::DirectWriter(QIODevice *device, QObject *parent)
 : AbstractWriter(device, parent)
{
}

}} // namespace Mdt{ namespace SerialPort{
