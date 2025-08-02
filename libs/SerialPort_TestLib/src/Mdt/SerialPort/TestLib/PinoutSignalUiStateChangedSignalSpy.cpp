// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PinoutSignalUiStateChangedSignalSpy.h"

namespace Mdt{ namespace SerialPort{ namespace TestLib{

void PinoutSignalUiStateChangedSignalSpy::appendStateIsOnChanged(bool on)
{
  mStateList.push_back(on);
}

void PinoutSignalUiStateChangedSignalSpy::clear() noexcept
{
  mStateList.clear();
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
