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

  const auto it = std::find_if(mAvailablePortList.cbegin(), mAvailablePortList.cend(), pred);
  assert( it != mAvailablePortList.cend() );

  mAvailablePortList.erase(it);
}

const TestPortInfo & TestPortInfoListTableModel::portInfoAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  return mList.atRow(row);
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
