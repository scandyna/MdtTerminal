// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
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
    return currentPort.portName == port.portName;
  };

  const auto it = std::find_if(mAvailablePortList.cbegin(), mAvailablePortList.cend(), pred);
  assert( it != mAvailablePortList.cend() );

  /*
   * In Qt5, QVector::erase() expects an iterator, not a const_iterator.
   * Passing iterator to find_if() could maybe detach ?
   * So, lets get the index and use removeAt().
   * Also, this is a test class, we should never have more than 10 elements,
   * so simply cast the return type from std::distance() to int.
   *
   * A cleaner solution would be using an adapter, as proposed here:
   * https://gitlab.com/scandyna/mdtmodelview/-/issues/1
   */

  const int index = static_cast<int>( std::distance(mAvailablePortList.cbegin(), it) );

  mAvailablePortList.removeAt(index);
}

const TestPortInfo & TestPortInfoListTableModel::portInfoAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  return mList.at(row);
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
