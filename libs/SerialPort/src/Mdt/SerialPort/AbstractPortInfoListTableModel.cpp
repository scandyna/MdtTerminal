// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "AbstractPortInfoListTableModel.h"
#include "PortInfoStringFormat.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

AbstractPortInfoListTableModel::AbstractPortInfoListTableModel(QObject *parent)
 : AbstractTableModel(parent)
{
}

void AbstractPortInfoListTableModel::fetchAvailablePorts()
{
  beginResetModel();
  doFetchAvailablePorts();
  endResetModel();
}

QString AbstractPortInfoListTableModel::portNameAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  return doGetPortNameAtRow(row);
}

std::optional<quint16> AbstractPortInfoListTableModel::vendorIdentifierAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  return doGetVendorIdentifierAtRow(row);
}

std::optional<quint16> AbstractPortInfoListTableModel::productIdentifierAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  return doGetProductIdentifierAtRow(row);
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

QVariant AbstractPortInfoListTableModel::displayRoleData(const QModelIndex & index) const noexcept
{
  assert( indexIsValidAndInRange(index) );

  const auto column = static_cast<Column>( index.column() );
  switch(column){
    case Column::PortName:
      return doGetPortNameAtRow( index.row() );
    case Column::SystemLocation:
      return doGetSystemLocationAtRow( index.row() );
    case Column::Description:
      return doGetDescriptionAtRow( index.row() );
    case Column::Manufacturer:
      return doGetManufacturerAtRow( index.row() );
    case Column::SerialNumber:
      return doGetSerialNumberAtRow( index.row() );
    case Column::VendorIdentifier:
      return PortInfoStringFormat::vendorIdentifierToString( vendorIdentifierAtRow( index.row() ) );
    case Column::ProductIdentifier:
      return PortInfoStringFormat::productIdentifierToString( productIdentifierAtRow( index.row() ) );
  }

  return QVariant();
}

}} // namespace Mdt{ namespace SerialPort{
