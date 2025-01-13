// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "AbstractPortInfoListTableModel.h"
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
      return doGetVendorIdentifierAtRow( index.row() );
    case Column::ProductIdentifier:
      return doGetProductIdentifierAtRow( index.row() );
  }

  return QVariant();
}

}} // namespace Mdt{ namespace SerialPort{
