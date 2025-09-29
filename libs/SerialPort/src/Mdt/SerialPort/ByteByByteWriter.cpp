// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "ByteByByteWriter.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

ByteByByteWriter::ByteByByteWriter(QIODevice *device, QObject *parent)
 : AbstractByteByByteWriter(device, parent)
{
  mTimer.setSingleShot(true);
  mTimer.setTimerType(Qt::CoarseTimer); // 5% of the desired interval
  connect(&mTimer, &QTimer::timeout, this, &ByteByByteWriter::setTimerTimeoutEvent);
}

void ByteByByteWriter::setInterval(std::chrono::milliseconds t) noexcept
{
  mTimer.setInterval(t);
}

void ByteByByteWriter::startTimer()
{
  mTimer.start();
}

void ByteByByteWriter::stopTimer()
{
  mTimer.stop();
}

}} // namespace Mdt{ namespace SerialPort{
