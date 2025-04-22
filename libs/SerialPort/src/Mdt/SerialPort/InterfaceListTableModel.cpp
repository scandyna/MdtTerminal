// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "InterfaceListTableModel.h"
#include "InterfaceStringFormat.h"

namespace Mdt{ namespace SerialPort{

InterfaceListTableModel::InterfaceListTableModel(QObject *parent)
 : AbstractTableModel(parent)
{
}

void InterfaceListTableModel::setVendorIdentifierAndProductIdentifier(std::optional<quint16> vid, std::optional<quint16> pid)
{
  InterfaceList newList;

  if( vid.has_value() && pid.has_value() ){
    newList = InterfaceList::fromVendorIdentifierAndProductIdentifier(*vid, *pid);
  }

  bool shouldResetModel = true;

  if( mList.container().has_value() ){
    if( newList.count() == mList.container()->count() ){
      shouldResetModel = false;
    }
  }

  if(shouldResetModel){
    beginResetModel();
    mList.containerMutable() = newList;
    endResetModel();
  }else{
    mList.containerMutable() = newList;
    const int count = rowCount();
    for(int row = 0; row < count; ++row){
      emitRowDataChanged(row);
    }
  }
}

void InterfaceListTableModel::clear()
{
  beginResetModel();
  mList.containerMutable().reset();
  endResetModel();
}

int InterfaceListTableModel::findRowOfStandard(InterfaceStandard standard) const
{
  if( !mList.container().has_value() ){
    return -1;
  }

  const auto index = mList.container()->findIndexOfStandard(standard);
  if( index.has_value() ){
    return mList.rowFromIndex(*index);
  }

  return -1;
}

const Interface & InterfaceListTableModel::interfaceAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  return mList.atRow(row);
}

QVariant InterfaceListTableModel::displayRoleData(const QModelIndex & index) const noexcept
{
  assert( indexIsValidAndInRange(index) );

  const auto column = static_cast<Column>( index.column() );
  switch(column){
    case Column::Name:
      return InterfaceStringFormat::standardName( mList.atRow( index.row() ).standard() );
    case Column::ParameterValue:
      return mList.atRow( index.row() ).parameterValue();
  }

  return QVariant();
}

}} // namespace Mdt{ namespace SerialPort{
