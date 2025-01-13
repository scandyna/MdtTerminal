// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortInfoListTableModel.h"
#include "PortInfoStringFormat.h"

namespace Mdt{ namespace SerialPort{

PortInfoListTableModel::PortInfoListTableModel(QObject *parent)
 : AbstractPortInfoListTableModel(parent)
{
}

void PortInfoListTableModel::doFetchAvailablePorts()
{
  mList = QSerialPortInfo::availablePorts();
}

QString PortInfoListTableModel::doGetVendorIdentifierAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  return PortInfoStringFormat::vendorIdentifierToString(mList[row]);
}

QString PortInfoListTableModel::doGetProductIdentifierAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  return PortInfoStringFormat::productIdentifierToString(mList[row]);
}

}} // namespace Mdt{ namespace SerialPort{
