// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "TestPortInfoListTableModel.h"

namespace Mdt{ namespace SerialPort{ namespace TestLib{

TestPortInfoListTableModel::TestPortInfoListTableModel(QObject *parent)
: AbstractPortInfoListTableModel(parent)
{
}

const TestPortInfo & TestPortInfoListTableModel::portInfoAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  return mList.at(row);
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
