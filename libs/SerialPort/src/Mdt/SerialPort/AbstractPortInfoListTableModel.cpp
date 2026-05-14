// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "AbstractPortInfoListTableModel.h"
#include "PortInfoStringFormat.h"
#include "Algorithm.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

AbstractPortInfoListTableModel::AbstractPortInfoListTableModel(QObject *parent)
 : AbstractTableModel(parent)
{
}

void AbstractPortInfoListTableModel::fetchAvailablePorts(PortListSorting sorting)
{
  beginResetModel();
  mList.containerMutable().clear();
  doFetchAvailablePorts();
  if(sorting == PortListSorting::ByPortName){
    sortPortInfoListByPortName( mList.containerMutable() );
  }
  endResetModel();
}

QString AbstractPortInfoListTableModel::portNameAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  return portInfoAtRow(row).portName();
}

int AbstractPortInfoListTableModel::findRowOfPortName(const QString & name) const noexcept
{
  const int count = rowCount();

  for(int row = 0; row < count; ++row){
    if( portNameAtRow(row) == name ){
      return row;
    }
  }

  return -1;
}

void AbstractPortInfoListTableModel::addPortInfo(const PortInfo & portInfo) noexcept
{
  assert( !portInfo.isNull() );

  mList.containerMutable().push_back(portInfo);
}

QVariant AbstractPortInfoListTableModel::displayRoleData(const QModelIndex & index) const noexcept
{
  assert( indexIsValidAndInRange(index) );

  const PortInfo & portInfo = portInfoAtRow( index.row() );
  const auto column = static_cast<Column>( index.column() );
  switch(column){
    case Column::PortName:
      return portInfo.portName();
    case Column::SystemLocation:
      return portInfo.systemLocation();
    case Column::Description:
      return portInfo.description();
    case Column::Manufacturer:
      return portInfo.manufacturer();
    case Column::SerialNumber:
      return portInfo.serialNumber();
    case Column::VendorIdentifier:
      return PortInfoStringFormat::vendorIdentifierToString(portInfo);
    case Column::ProductIdentifier:
      return PortInfoStringFormat::productIdentifierToString(portInfo);
  }

  return QVariant();
}

}} // namespace Mdt{ namespace SerialPort{
