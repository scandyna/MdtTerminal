// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include <QComboBox>
#include <QLatin1String>
#include <QStringBuilder>
#include <QSerialPort>
#include <cassert>

// #include <QDebug>

namespace Mdt{ namespace SerialPort{

SettingsDialog::SettingsDialog(QWidget* parent)
 : QDialog(parent),
   mUi( std::make_unique<Ui::SettingsDialog>() )
{
  mUi->setupUi(this);

  connect(mUi->serialPortListBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &SettingsDialog::showPortInfoForRow);

  mUi->baudRateBox->setModel( mEditor.baudRateListModelForView() );
  mUi->baudRateBox->setModelColumn(0);

  connect(&mEditor, &SettingsEditor::baudRateListCurrentRowChanged, mUi->baudRateBox, &QComboBox::setCurrentIndex);
  connect(mUi->baudRateBox, &QComboBox::currentIndexChanged, &mEditor, &SettingsEditor::setBaudRateListCurrentRowFromUi);

  mUi->dataBitsBox->setModel( mEditor.dataBitsListModelForView() );
  mUi->dataBitsBox->setModelColumn(0);

  connect(&mEditor, &SettingsEditor::dataBitsListCurrentRowChanged, mUi->dataBitsBox, &QComboBox::setCurrentIndex);
  connect(mUi->dataBitsBox, &QComboBox::currentIndexChanged, &mEditor, &SettingsEditor::setDataBitsListCurrentRowFromUi);

  mUi->parityBox->setModel( mEditor.parityListModelForView() );
  mUi->parityBox->setModelColumn(0);

  connect(&mEditor, &SettingsEditor::parityListCurrentRowChanged, mUi->parityBox, &QComboBox::setCurrentIndex);
  connect(mUi->parityBox, &QComboBox::currentIndexChanged, &mEditor, &SettingsEditor::setParityListCurrentRowFromUi);

  mUi->flowControlBox->setModel( mEditor.flowControlListModelForView() );
  mUi->flowControlBox->setModelColumn(0);

  connect(&mEditor, &SettingsEditor::flowControlListCurrentRowChanged, mUi->flowControlBox, &QComboBox::setCurrentIndex);
  connect(mUi->flowControlBox, &QComboBox::currentIndexChanged, &mEditor, &SettingsEditor::setFlowControlListCurrentRowFromUi);

  fetchAvailablePorts();
  fillAvailablePortSettings();
}

SettingsDialog::~SettingsDialog() noexcept = default;

void SettingsDialog::setSettings(const Settings & settings)
{
  mEditor.setSettings(settings);
}

void SettingsDialog::fetchAvailablePorts()
{
  mUi->serialPortListBox->clear();

  mAvailablePorts = QSerialPortInfo::availablePorts();
  for(const QSerialPortInfo & portInfo : mAvailablePorts){
    mUi->serialPortListBox->addItem( portInfo.portName() );
  }
}

void SettingsDialog::showPortInfoForRow(int row) noexcept
{
  if(row < 0){
    return;
  }
  assert( row < mAvailablePorts.size() );

  const QSerialPortInfo portInfo = mAvailablePorts.at(row);
  mUi->description->setText( portInfo.description() );
  mUi->manufacturer->setText( portInfo.manufacturer() );
  mUi->serialNumber->setText( portInfo.serialNumber() );
  mUi->location->setText( portInfo.systemLocation() );
  mUi->vid->setText( formatVid(portInfo) );
  mUi->pid->setText( formatPid(portInfo) );
}

void SettingsDialog::fillAvailablePortSettings() noexcept
{
  mEditor.fetchAvailablePortSettings();

  fillAvailableStopBits();
  // fillAvailableFlowControls();
}

void SettingsDialog::fillAvailableStopBits() noexcept
{
  mUi->stopBitsBox->addItem(QLatin1String("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
  mUi->stopBitsBox->addItem(QLatin1String("1.5"), QSerialPort::OneAndHalfStop);
#endif
  mUi->stopBitsBox->addItem(QLatin1String("2"), QSerialPort::TwoStop);
}

// void SettingsDialog::fillAvailableFlowControls() noexcept
// {
//   mUi->flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
//   mUi->flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
//   mUi->flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
// }

QString SettingsDialog::formatVid(const QSerialPortInfo & portInfo) noexcept
{
  if( portInfo.hasVendorIdentifier() ){
    return QLatin1String("0x") % QString::number(portInfo.vendorIdentifier(), 16);
  }
  return QString();
}

QString SettingsDialog::formatPid(const QSerialPortInfo& portInfo) noexcept
{
  if( portInfo.hasProductIdentifier() ){
    return QLatin1String("0x") % QString::number(portInfo.productIdentifier(), 16);
  }
  return QString();
}

}} // namespace Mdt{ namespace SerialPort{
