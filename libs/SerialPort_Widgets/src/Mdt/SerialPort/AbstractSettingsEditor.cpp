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
#include "Mdt/SerialPort/SettingsRawData.h"
#include "Mdt/SerialPort/SettingsBuilder.h"
#include <cassert>

// #include <QDebug>

namespace Mdt{ namespace SerialPort{

AbstractSettingsEditor::AbstractSettingsEditor(QObject* parent)
 : QObject(parent)
{
}

int AbstractSettingsEditor::portNameColumnInPortInfoListModelForView() const noexcept
{
  return AbstractPortInfoListTableModel::portNameColumnIndex();
}

QString AbstractSettingsEditor::currentPortName() const noexcept
{
  assert( hasPortInfoListCurrentRow() );
  assert( constPortInfoListTableModel()->rowIndexIsInRange(mPortInfoListCurrentRow) );

  return constPortInfoListTableModel()->portNameAtRow(mPortInfoListCurrentRow);
}

void AbstractSettingsEditor::fetchAvailablePorts()
{
  doFetchAvailablePorts();
}

void AbstractSettingsEditor::fetchAvailablePortSettings()
{
  fetchStandardBaudRates();
}

void AbstractSettingsEditor::setSettings(const Settings & settings)
{
  setCurrentPortName( settings.portName() );
  setCurrentBaudRate(settings);
  setCurrentDataBits(settings);
  setCurrentParity(settings);
  setCurrentFlowControl(settings);
  setCurrentStopBits(settings);
  setCurrentInterfaceStandard( settings.interfaceStandard() );
  setSendByteByByteEnabled( settings.sendByteByByteIsEnabled() );
  if( settings.sendByteByByteIsEnabled() ){
    setSendByteByByteIntervalInMilliseconds( settings.sendByteByByteSettings().rawIntervalInMilliseconds() );
  }
}

Settings AbstractSettingsEditor::buildSettings() const
{
  assert( hasPortInfoListCurrentRow() );

  SettingsRawData settingsData;
  settingsData.portName = currentPortName();
  settingsData.baudRate = currentBaudRate();
  settingsData.dataBits = currentDataBits();
  settingsData.parity = currentParity();
  settingsData.flowControl = currentFlowControl();
  settingsData.stopBits = currentStopBits();
  settingsData.interfaceStandard = currentInterface().standard();
  settingsData.sendByteByByteIsEnabled = mSendByteByByteIsEnabled;
  settingsData.sendByteByByteIntervalInMilliseconds = mSendByteByByteIntervalInMilliseconds;

  return SettingsBuilder::settingsFromRawData(settingsData);
}

void AbstractSettingsEditor::setPortInfoListCurrentRowFromUi(int row) noexcept
{
  assert( row < portInfoListModelForView()->rowCount() );

  /*
   * When a user plugs/unplugs a removable serial port (like UBS-serial interfaces),
   * then refreshes the list of available ports,
   * we can end up with the same row as before, but with another port info
   * So, better notify changed everytime.
   * (Views like QCombobox also has logic to emit currentIndexChanged the appropriate time)
   */
  mPortInfoListCurrentRow = row;
  fetchPortSpecificAttributes();
  doNotifyPortInfoChanged(row);
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

void AbstractSettingsEditor::setInterfaceListCurrentRowFromUi(int row) noexcept
{
  assert( rowIsMinusOneOrInRangeOfInterfaceList(row) );

  mInterfaceListCurrentRow = row;
}

void AbstractSettingsEditor::setSendByteByByteEnabledFromUi(bool enabled) noexcept
{
  mSendByteByByteIsEnabled = enabled;
}

void AbstractSettingsEditor::setSendByteByByteIntervalInMillisecondsFromUi(int interval) noexcept
{
  mSendByteByByteIntervalInMilliseconds = interval;
}

void AbstractSettingsEditor::fetchStandardBaudRates()
{
  mBaudRateListTableModel.fetchStandardBaudRates();
}

void AbstractSettingsEditor::fetchPortSpecificAttributes()
{
  const int row = mPortInfoListCurrentRow;
  if(row < 0){
    mInterfaceListTableModel.clear();
    return;
  }

  const auto *model = portInfoListTableModel();
  assert(model != nullptr);
  assert( model->rowIndexIsInRange(row) );

  const auto vid = model->vendorIdentifierAtRow(row);
  const auto pid = model->productIdentifierAtRow(row);

  mInterfaceListTableModel.setVendorIdentifierAndProductIdentifier(vid, pid);
}

void AbstractSettingsEditor::setCurrentPortName(const QString & name)
{
  const int row = constPortInfoListTableModel()->findRowOfPortName(name);

  if(row == mPortInfoListCurrentRow){
    return;
  }

  if(row < 0){
    if( constPortInfoListTableModel()->rowCount() == 0 ){
      mPortInfoListCurrentRow = -1;
    }else{
      mPortInfoListCurrentRow = 0;
    }
  }else{
    mPortInfoListCurrentRow = row;
  }
  assert( rowIsMinusOneOrInRangeOfPortInfoList(mPortInfoListCurrentRow) );

  emit portInfoListCurrentRowChanged(mPortInfoListCurrentRow);
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

/*
 * See remarks in the tests (SerialPortSettingsEditorTest.cpp)
 */
void AbstractSettingsEditor::setCurrentInterfaceStandard(InterfaceStandard standard)
{
  int row = mInterfaceListTableModel.findRowOfStandard(standard);
  assert( rowIsMinusOneOrInRangeOfInterfaceList(row) );

  if( (row == -1) && (mInterfaceListTableModel.rowCount() > 0) ){
    row = 0;
  }
  if(row == mInterfaceListCurrentRow){
    return;
  }

  mInterfaceListCurrentRow = row;
  emit interfaceListCurrentRowChanged(row);
}

void AbstractSettingsEditor::setSendByteByByteEnabled(bool enabled)
{
  if(enabled == mSendByteByByteIsEnabled){
    return;
  }

  mSendByteByByteIsEnabled = enabled;
  emit sendByteByByteIsEnabledChanged(enabled);
}

void AbstractSettingsEditor::setSendByteByByteIntervalInMilliseconds(int interval)
{
  if(interval == mSendByteByByteIntervalInMilliseconds){
    return;
  }

  mSendByteByByteIntervalInMilliseconds = interval;
  emit sendByteByByteIntervalInMillisecondsChanged(interval);
}

qint32 AbstractSettingsEditor::currentBaudRate() const noexcept
{
  assert( mBaudRateListTableModel.rowIndexIsInRange(mBaudRateListCurrentRow) );

  return mBaudRateListTableModel.baudRateAtRow(mBaudRateListCurrentRow);
}

QSerialPort::DataBits AbstractSettingsEditor::currentDataBits() const noexcept
{
  assert( mDataBitsListTableModel.rowIndexIsInRange(mDataBitsListCurrentRow) );

  return mDataBitsListTableModel.dataBitsAtRow(mDataBitsListCurrentRow);
}

QSerialPort::Parity AbstractSettingsEditor::currentParity() const noexcept
{
  assert( mParityListTableModel.rowIndexIsInRange(mParityListCurrentRow) );

  return mParityListTableModel.parityAtRow(mParityListCurrentRow);
}

QSerialPort::FlowControl AbstractSettingsEditor::currentFlowControl() const noexcept
{
  assert( mFlowControlListTableModel.rowIndexIsInRange(mFlowControlListCurrentRow) );

  return mFlowControlListTableModel.flowControlAtRow(mFlowControlListCurrentRow);
}

QSerialPort::StopBits AbstractSettingsEditor::currentStopBits() const noexcept
{
  assert( mStopBitsListTableModel.rowIndexIsInRange(mStopBitsListCurrentRow) );

  return mStopBitsListTableModel.stopBitsAtRow(mStopBitsListCurrentRow);
}

const Interface & AbstractSettingsEditor::currentInterface() const noexcept
{
  assert( mInterfaceListTableModel.rowIndexIsInRange(mInterfaceListCurrentRow) );

  return mInterfaceListTableModel.interfaceAtRow(mInterfaceListCurrentRow);
}


bool AbstractSettingsEditor::rowIsMinusOneOrInRangeOfPortInfoList(int row) const noexcept
{
  if(row == -1){
    return true;
  }

  return constPortInfoListTableModel()->rowIndexIsInRange(row);
}

bool AbstractSettingsEditor::rowIsMinusOneOrInRangeOfInterfaceList(int row) const noexcept
{
  if(row == -1){
    return true;
  }

  return mInterfaceListTableModel.rowIndexIsInRange(row);
}

}} // namespace Mdt{ namespace SerialPort{
