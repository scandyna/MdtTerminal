// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsEditor.h"
#include <cassert>

// #include <QDebug>

namespace Mdt{ namespace SerialPort{

SettingsEditor::SettingsEditor(QObject* parent)
 : AbstractSettingsEditor(parent)
{
}

void SettingsEditor::doNotifyPortInfoChanged(int row) const
{
  if(row < 0){
    emit portInfoChanged( QSerialPortInfo() );
    return;
  }
  assert( mPortInfoListTableModel.rowIndexIsInRange(row) );

  emit portInfoChanged( mPortInfoListTableModel.portInfoAtRow(row) );
}

}} // namespace Mdt{ namespace SerialPort{
