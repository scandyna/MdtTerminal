// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "StopBitsListTableModel.h"
#include "StopBitsStringFormat.h"
#include "Settings.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

StopBitsListTableModel::StopBitsListTableModel(QObject *parent)
 : AbstractTableModel(parent)
{
}

int StopBitsListTableModel::findRowOfStopBits(QSerialPort::StopBits bits) const noexcept
{
  if(bits == QSerialPort::OneStop){
    return 0;
  }

  if constexpr( oneAndHalfStopBitsIsSupported() ){
    switch(bits){
      case QSerialPort::OneAndHalfStop:
        return 1;
      case QSerialPort::TwoStop:
        return 2;
      default:
        break;
    }
  }
  assert(bits == QSerialPort::TwoStop);

  return 1;
}

QSerialPort::StopBits StopBitsListTableModel::stopBitsAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  if(row == 0){
    return QSerialPort::OneStop;
  }

  if constexpr( oneAndHalfStopBitsIsSupported() ){
    switch(row){
      case 1:
        return QSerialPort::OneAndHalfStop;
      case 2:
        return QSerialPort::TwoStop;
    }
  }
  assert(row == 1);

  return QSerialPort::TwoStop;
}

int StopBitsListTableModel::rowCountWithoutParentIndex() const noexcept
{
  if constexpr( oneAndHalfStopBitsIsSupported() ){
    return 3;
  }
  return 2;
}

QVariant StopBitsListTableModel::displayRoleData(const QModelIndex & index) const noexcept
{
  assert( indexIsValidAndInRange(index) );

  return StopBitsStringFormat::stopBitsToString( stopBitsAtRow( index.row() ) );
}

}} // namespace Mdt{ namespace SerialPort{
