// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
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

std::optional<quint16> PortInfoListTableModel::doGetVendorIdentifierAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  if( mList[row].hasVendorIdentifier() ){
    return mList[row].vendorIdentifier();
  }

  return {};
}

std::optional<quint16> PortInfoListTableModel::doGetProductIdentifierAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  if( mList[row].hasProductIdentifier() ){
    return mList[row].productIdentifier();
  }

  return {};
}

}} // namespace Mdt{ namespace SerialPort{
