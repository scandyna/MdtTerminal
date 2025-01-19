// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "TestSettingsEditor.h"
#include <cassert>

using Mdt::SerialPort::TestLib::TestPortInfo;

TestSettingsEditor::TestSettingsEditor(QObject* parent)
 : AbstractSettingsEditor(parent)
{
}

void TestSettingsEditor::doNotifyPortInfoChanged(int row) const
{
  if(row < 0){
    mCurrentPortInfo = TestPortInfo{};
    return;
  }
  assert( mPortInfoListTableModel.rowIndexIsInRange(row) );

  mCurrentPortInfo = mPortInfoListTableModel.portInfoAtRow(row);
}
