// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "DataBitsListTableModel.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

DataBitsListTableModel::DataBitsListTableModel(QObject *parent)
 : AbstractTableModel(parent)
{
}

int DataBitsListTableModel::findRowOfDataBits(QSerialPort::DataBits dataBits) const noexcept
{
  /*
   * UnknownDataBits is not documented, so consider it does no exist
   * Qt doc: https://doc.qt.io/qt-6/qserialport.html#DataBits-enum
   * NOTE: it was deprecated in Qt5
   */
  assert(dataBits != QSerialPort::UnknownDataBits);

  switch(dataBits){
    case QSerialPort::Data5:
      return 0;
    case QSerialPort::Data6:
      return 1;
    case QSerialPort::Data7:
      return 2;
    case QSerialPort::Data8:
      return 3;
    case QSerialPort::UnknownDataBits:
      break;
  }

  // Should never happen
  return -1;
}

QSerialPort::DataBits DataBitsListTableModel::dataBitsAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  switch(row){
    case 0:
      return QSerialPort::Data5;
    case 1:
      return QSerialPort::Data6;
    case 2:
      return QSerialPort::Data7;
    case 3:
      return QSerialPort::Data8;
  }

  // Should never happen
  return QSerialPort::UnknownDataBits;
}

QVariant DataBitsListTableModel::displayRoleData(const QModelIndex & index) const noexcept
{
  assert( indexIsValidAndInRange(index) );

  switch( index.row() ){
    case 0:
      return 5;
    case 1:
      return 6;
    case 2:
      return 7;
    case 3:
      return 8;
  }

  return QVariant();
}

}} // namespace Mdt{ namespace SerialPort{
