// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "AbstractSettingsEditor.h"
#include "Mdt/SerialPort/AbstractPortInfoListTableModel.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

AbstractSettingsEditor::AbstractSettingsEditor(QObject* parent)
 : QObject(parent)
{
}

int AbstractSettingsEditor::portNameColumnInPortInfoListModelForView() const noexcept
{
  return AbstractPortInfoListTableModel::portNameColumnIndex();
}

void AbstractSettingsEditor::fetchAvailablePortSettings()
{
  fetchStandardBaudRates();
}

void AbstractSettingsEditor::setSettings(const Settings & settings)
{
  setCurrentBaudRate(settings);
  setCurrentDataBits(settings);
  setCurrentParity(settings);
  setCurrentFlowControl(settings);
  setCurrentStopBits(settings);
}

void AbstractSettingsEditor::setPortInfoListCurrentRowFromUi(int row) noexcept
{
  assert( row < portInfoListModelForView()->rowCount() );

  const bool shouldNotifyChange = mPortInfoListCurrentRow != row;

  mPortInfoListCurrentRow = row;

  if(shouldNotifyChange){
    doNotifyPortInfoChanged(row);
  }
}

void AbstractSettingsEditor::setBaudRateListCurrentRowFromUi(int row) noexcept
{
  /// assert( mBaudRateListTableModel.rowIndexIsInRange(row) );

  mBaudRateListCurrentRow = row;
}

void AbstractSettingsEditor::setDataBitsListCurrentRowFromUi(int row) noexcept
{
  assert( mDataBitsListTableModel.rowIndexIsInRange(row) );

  mDataBitsListCurrentRow = row;
}

void AbstractSettingsEditor::setParityListCurrentRowFromUi(int row) noexcept
{
  assert( mParityListTableModel.rowIndexIsInRange(row) );

  mParityListCurrentRow = row;
}

void AbstractSettingsEditor::setFlowControlListCurrentRowFromUi(int row) noexcept
{
  assert( mFlowControlListTableModel.rowIndexIsInRange(row) );

  mFlowControlListCurrentRow = row;
}

void AbstractSettingsEditor::setStopBitsListCurrentRowFromUi(int row) noexcept
{
  assert( mStopBitsListTableModel.rowIndexIsInRange(row) );

  mStopBitsListCurrentRow = row;
}

void AbstractSettingsEditor::fetchStandardBaudRates()
{
  mBaudRateListTableModel.fetchStandardBaudRates();
}

void AbstractSettingsEditor::setCurrentBaudRate(const Settings & settings)
{
  const int row = mBaudRateListTableModel.findRowOfBaudRate( settings.baudRate() );
  if(row == mBaudRateListCurrentRow){
    return;
  }

  mBaudRateListCurrentRow = row;
  /// \todo If row < 0, its a custom baud rate - Implement this - NO
  emit baudRateListCurrentRowChanged(row);
}

void AbstractSettingsEditor::setCurrentDataBits(const Settings & settings)
{
  const int row = mDataBitsListTableModel.findRowOfDataBits( settings.dataBits() );
  assert( mDataBitsListTableModel.rowIndexIsInRange(row) );
  if(row == mDataBitsListCurrentRow){
    return;
  }

  mDataBitsListCurrentRow = row;
  emit dataBitsListCurrentRowChanged(row);
}

void AbstractSettingsEditor::setCurrentParity(const Settings & settings)
{
  const int row = mParityListTableModel.findRowOfParity( settings.parity() );
  assert( mParityListTableModel.rowIndexIsInRange(row) );
  if(row == mParityListCurrentRow){
    return;
  }

  mParityListCurrentRow = row;
  emit parityListCurrentRowChanged(row);
}

void AbstractSettingsEditor::setCurrentFlowControl(const Settings & settings)
{
  const int row = mFlowControlListTableModel.findRowOfFlowControl( settings.flowControl() );
  assert( mFlowControlListTableModel.rowIndexIsInRange(row) );
  if(row == mFlowControlListCurrentRow){
    return;
  }

  mFlowControlListCurrentRow = row;
  emit flowControlListCurrentRowChanged(row);
}

void AbstractSettingsEditor::setCurrentStopBits(const Settings & settings)
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
