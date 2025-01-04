// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
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
  mList = QSerialPortInfo::standardBaudRates();
  endResetModel();
}

void BaudRateListTableModel::setBaudRateList(const QList<qint32> & list)
{
  beginResetModel();
  mList = list;
  endResetModel();
}

int BaudRateListTableModel::findRowOfBaudRate(qint32 baudRate) const noexcept
{
  return mList.indexOf(baudRate);
}

QVariant BaudRateListTableModel::displayRoleData(const QModelIndex & index) const noexcept
{
  assert( indexIsValidAndInRange(index) );

  return mList[index.row()];
}

}} // namespace Mdt{ namespace SerialPort{
