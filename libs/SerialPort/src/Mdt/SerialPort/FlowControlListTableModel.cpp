// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "FlowControlListTableModel.h"
#include "FlowControlStringFormat.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

FlowControlListTableModel::FlowControlListTableModel(QObject *parent)
 : AbstractTableModel(parent)
{
}

int FlowControlListTableModel::findRowOfFlowControl(QSerialPort::FlowControl control) const noexcept
{
  /*
   * UnknownFlowControl is not documented, so consider it does no exist
   * Qt doc: https://doc.qt.io/qt-6/qserialport.html#FlowControl-enum
   * NOTE: it was deprecated in Qt5
   */
  assert(control != QSerialPort::UnknownFlowControl);

  switch(control){
    case QSerialPort::NoFlowControl:
      return 0;
    case QSerialPort::HardwareControl:
      return 1;
    case QSerialPort::SoftwareControl:
      return 2;
    case QSerialPort::UnknownFlowControl:
      break;
  }

  // Should never happen
  return -1;
}

QSerialPort::FlowControl FlowControlListTableModel::flowControlAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  switch(row){
    case 0:
      return QSerialPort::NoFlowControl;
    case 1:
      return QSerialPort::HardwareControl;
    case 2:
      return QSerialPort::SoftwareControl;
  }

  // Should never happen
  return QSerialPort::UnknownFlowControl;
}

QVariant FlowControlListTableModel::displayRoleData(const QModelIndex & index) const noexcept
{
  assert( indexIsValidAndInRange(index) );

  return FlowControlStringFormat::flowControlToString( flowControlAtRow( index.row() ) );
}

}} // namespace Mdt{ namespace SerialPort{
