// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsEditor.h"
#include <cassert>

// #include <QDebug>

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
  setCurrentBaudRate(settings);
  setCurrentDataBits(settings);
  setCurrentParity(settings);
  setCurrentFlowControl(settings);
  setCurrentStopBits(settings);
}

void SettingsEditor::setBaudRateListCurrentRowFromUi(int row) noexcept
{
  /// assert( mBaudRateListTableModel.rowIndexIsInRange(row) );

  mBaudRateListCurrentRow = row;
}

void SettingsEditor::setDataBitsListCurrentRowFromUi(int row) noexcept
{
  assert( mDataBitsListTableModel.rowIndexIsInRange(row) );

  mDataBitsListCurrentRow = row;
}

void SettingsEditor::setParityListCurrentRowFromUi(int row) noexcept
{
  assert( mParityListTableModel.rowIndexIsInRange(row) );

  mParityListCurrentRow = row;
}

void SettingsEditor::setFlowControlListCurrentRowFromUi(int row) noexcept
{
  assert( mFlowControlListTableModel.rowIndexIsInRange(row) );

  mFlowControlListCurrentRow = row;
}

void SettingsEditor::setStopBitsListCurrentRowFromUi(int row) noexcept
{
  assert( mStopBitsListTableModel.rowIndexIsInRange(row) );

  mStopBitsListCurrentRow = row;
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

void SettingsEditor::setCurrentParity(const Settings & settings)
{
  const int row = mParityListTableModel.findRowOfParity( settings.parity() );
  assert( mParityListTableModel.rowIndexIsInRange(row) );
  if(row == mParityListCurrentRow){
    return;
  }

  mParityListCurrentRow = row;
  emit parityListCurrentRowChanged(row);
}

void SettingsEditor::setCurrentFlowControl(const Settings & settings)
{
  const int row = mFlowControlListTableModel.findRowOfFlowControl( settings.flowControl() );
  assert( mFlowControlListTableModel.rowIndexIsInRange(row) );
  if(row == mFlowControlListCurrentRow){
    return;
  }

  mFlowControlListCurrentRow = row;
  emit flowControlListCurrentRowChanged(row);
}

void SettingsEditor::setCurrentStopBits(const Settings & settings)
{
  const int row = mStopBitsListTableModel.findRowOfStopBits( settings.stopBits() );
  assert( mStopBitsListTableModel.rowIndexIsInRange(row) );
  if(row == mStopBitsListCurrentRow){
    return;
  }

  mStopBitsListCurrentRow = row;
  emit stopBitsListCurrentRowChanged(row);
}

}} // namespace Mdt{ namespace SerialPort{
