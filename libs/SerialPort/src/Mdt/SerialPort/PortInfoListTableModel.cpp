// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortInfoListTableModel.h"
#include "PortInfoStringFormat.h"
#include "Algorithm.h"

namespace Mdt{ namespace SerialPort{

PortInfoListTableModel::PortInfoListTableModel(QObject *parent)
 : AbstractPortInfoListTableModel(parent)
{
}

void PortInfoListTableModel::doFetchAvailablePorts(PortListSorting sorting)
{
  mList.containerMutable() = QSerialPortInfo::availablePorts();
  if(sorting == PortListSorting::ByPortName){
    sortPortInfoListByPortName( mList.containerMutable() );
  }
}

std::optional<quint16> PortInfoListTableModel::doGetVendorIdentifierAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  if( mList.atRow(row).hasVendorIdentifier() ){
    return mList.atRow(row).vendorIdentifier();
  }

  return {};
}

std::optional<quint16> PortInfoListTableModel::doGetProductIdentifierAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  if( mList.atRow(row).hasProductIdentifier() ){
    return mList.atRow(row).productIdentifier();
  }

  return {};
}

}} // namespace Mdt{ namespace SerialPort{
