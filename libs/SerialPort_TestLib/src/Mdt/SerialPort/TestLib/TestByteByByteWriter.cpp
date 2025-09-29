// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "TestByteByByteWriter.h"

namespace Mdt{ namespace SerialPort{ namespace TestLib{

TestByteByByteWriter::TestByteByByteWriter(QIODevice *device, QObject *parent)
 : AbstractByteByByteWriter(device, parent)
{
}

bool TestByteByByteWriter::hasMoreToSend() const noexcept
{
  return AbstractByteByByteWriter::hasMoreToSend();
}

void TestByteByByteWriter::setTimerTimeoutEvent()
{
  AbstractByteByByteWriter::setTimerTimeoutEvent();
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
