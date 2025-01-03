// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsEditor.h"
#include <cassert>

#include <QDebug>

namespace Mdt{ namespace SerialPort{

SettingsEditor::SettingsEditor(QObject* parent)
 : QObject(parent)
{
}

void SettingsEditor::fetchAvailablePortSettings()
{
  fetchStandardBaudRates();
}

void SettingsEditor::setSettings(const Settings & settings)
{
  qDebug() << "SettingsEditor::setSettings() ...";

  setCurrentBaudRate(settings);
  setCurrentDataBits(settings);
}

void SettingsEditor::setBaudRateListCurrentRowFromUi(int row) noexcept
{
  /// assert( mBaudRateListTableModel.rowIndexIsInRange(row) );

  qDebug() << "SettingsEditor::setBaudRateListCurrentRowFromUi() row: " << row;

  mBaudRateListCurrentRow = row;
}

void SettingsEditor::setDataBitsListCurrentRowFromUi(int row) noexcept
{
  assert( mDataBitsListTableModel.rowIndexIsInRange(row) );

  mDataBitsListCurrentRow = row;
}

void SettingsEditor::fetchStandardBaudRates()
{
  mBaudRateListTableModel.fetchStandardBaudRates();
}

void SettingsEditor::setCurrentBaudRate(const Settings & settings)
{
  const int row = mBaudRateListTableModel.findRowOfBaudRate( settings.baudRate() );
  if(row == mBaudRateListCurrentRow){
    return;
  }

  mBaudRateListCurrentRow = row;
  /// \todo If row < 0, its a custom baud rate - Implement this
  emit baudRateListCurrentRowChanged(row);
}

void SettingsEditor::setCurrentDataBits(const Settings & settings)
{
  const int row = mDataBitsListTableModel.findRowOfDataBits( settings.dataBits() );
  assert( mDataBitsListTableModel.rowIndexIsInRange(row) );
  if(row == mDataBitsListCurrentRow){
    return;
  }

  mDataBitsListCurrentRow = row;
  emit dataBitsListCurrentRowChanged(row);
}

}} // namespace Mdt{ namespace SerialPort{
