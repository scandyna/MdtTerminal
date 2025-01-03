// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "ParityListTableModel.h"
#include "ParityStringFormat.h"

namespace Mdt{ namespace SerialPort{

ParityListTableModel::ParityListTableModel(QObject *parent)
 : AbstractTableModel(parent)
{
}

int ParityListTableModel::findRowOfParity(QSerialPort::Parity parity) const noexcept
{
  /*
   * UnknownParity is not documented, so consider it does no exist
   * Qt doc: https://doc.qt.io/qt-6/qserialport.html#DataBits-enum
   * NOTE: it was deprecated in Qt5
   */
  assert(parity != QSerialPort::UnknownParity);

  switch(parity){
    case QSerialPort::NoParity:
      return 0;
    case QSerialPort::EvenParity:
      return 1;
    case QSerialPort::OddParity:
      return 2;
    case QSerialPort::SpaceParity:
      return 3;
    case QSerialPort::MarkParity:
      return 4;
    case QSerialPort::UnknownParity:
      break;
  }

  // Should never happen
  return -1;
}

QSerialPort::Parity ParityListTableModel::parityAtRow(int row) const noexcept
{
  assert( rowIndexIsInRange(row) );

  switch(row){
    case 0:
      return QSerialPort::NoParity;
    case 1:
      return QSerialPort::EvenParity;
    case 2:
      return QSerialPort::OddParity;
    case 3:
      return QSerialPort::SpaceParity;
    case 4:
      return QSerialPort::MarkParity;
  }

  // Should never happen
  return QSerialPort::UnknownParity;
}

QVariant ParityListTableModel::displayRoleData(const QModelIndex & index) const noexcept
{
  assert( indexIsValidAndInRange(index) );

  return ParityStringFormat::parityToString( parityAtRow( index.row() ) );
}

}} // namespace Mdt{ namespace SerialPort{
