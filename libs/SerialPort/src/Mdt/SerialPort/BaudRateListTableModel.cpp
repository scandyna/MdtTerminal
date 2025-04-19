// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "BaudRateListTableModel.h"
#include <QSerialPortInfo>
#include <cassert>

namespace Mdt{ namespace SerialPort{

BaudRateListTableModel::BaudRateListTableModel(QObject *parent)
 : AbstractTableModel(parent)
{
}

void BaudRateListTableModel::fetchStandardBaudRates()
{
  beginResetModel();
  mList.containerMutable() = QSerialPortInfo::standardBaudRates();
  endResetModel();
}

void BaudRateListTableModel::setBaudRateList(const QList<qint32> & list)
{
  beginResetModel();
  mList.containerMutable() = list;
  endResetModel();
}

int BaudRateListTableModel::findRowOfBaudRate(qint32 baudRate) const noexcept
{
  const auto index = mList.container().indexOf(baudRate);
  if(index < 0){
    return -1;
  }

  return mList.rowFromIndex(index);
}

QVariant BaudRateListTableModel::displayRoleData(const QModelIndex & index) const noexcept
{
  assert( indexIsValidAndInRange(index) );

  return mList.atRow( index.row() );
}

}} // namespace Mdt{ namespace SerialPort{
