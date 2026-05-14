// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "TestPortInfoListTableModel.h"
#include <algorithm>
#include <iterator>
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace TestLib{

TestPortInfoListTableModel::TestPortInfoListTableModel(QObject *parent)
: AbstractPortInfoListTableModel(parent)
{
}

void TestPortInfoListTableModel::removeAvailablePort(const TestPortInfo & port)
{
  const auto pred = [&port](const TestPortInfo & currentPort) -> bool {
    return currentPort.portName() == port.portName();
  };

  const auto it = std::remove_if(mAvailablePortList.begin(), mAvailablePortList.end(), pred);
  assert( it != mAvailablePortList.end() );

  mAvailablePortList.erase( it, mAvailablePortList.end() );
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
