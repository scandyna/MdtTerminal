// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsDialog.h"
#include "Mdt/SerialPort/PortInfoStringFormat.h"
#include "ui_SettingsDialog.h"
#include <QComboBox>
#include <QLatin1String>
#include <QStringBuilder>
#include <QSerialPort>
#include <cassert>

namespace Mdt{ namespace SerialPort{

SettingsDialog::SettingsDialog(QWidget* parent)
 : QDialog(parent),
   mUi( std::make_unique<Ui::SettingsDialog>() )
{
  mUi->setupUi(this);

  mUi->serialPortListBox->setModel( mEditor.portInfoListModelForView() );
  mUi->serialPortListBox->setModelColumn( mEditor.portNameColumnInPortInfoListModelForView() );

  connect(&mEditor, &SettingsEditor::portInfoListCurrentRowChanged, mUi->serialPortListBox, &QComboBox::setCurrentIndex);
  connect(&mEditor, &SettingsEditor::portInfoChanged, this, &SettingsDialog::showPortInfo);
  connect(mUi->serialPortListBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          &mEditor, &SettingsEditor::setPortInfoListCurrentRowFromUi);

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

  mUi->stopBitsBox->setModel( mEditor.stopBitsListModelForView() );
  mUi->stopBitsBox->setModelColumn(0);

  connect(&mEditor, &SettingsEditor::stopBitsListCurrentRowChanged, mUi->stopBitsBox, &QComboBox::setCurrentIndex);
  connect(mUi->stopBitsBox, &QComboBox::currentIndexChanged, &mEditor, &SettingsEditor::setStopBitsListCurrentRowFromUi);

  fetchAvailablePorts();
  fillAvailablePortSettings();
}

SettingsDialog::~SettingsDialog() noexcept = default;

void SettingsDialog::setSettings(const Settings & settings)
{
  mEditor.setSettings(settings);
}

void SettingsDialog::showPortInfo(const QSerialPortInfo & portInfo) noexcept
{
  mUi->description->setText( portInfo.description() );
  mUi->manufacturer->setText( portInfo.manufacturer() );
  mUi->serialNumber->setText( portInfo.serialNumber() );
  mUi->location->setText( portInfo.systemLocation() );
  mUi->vid->setText( PortInfoStringFormat::vendorIdentifierToString(portInfo) );
  mUi->pid->setText( PortInfoStringFormat::productIdentifierToString(portInfo) );
}

void SettingsDialog::fetchAvailablePorts()
{
  mEditor.fetchAvailablePorts();
}

void SettingsDialog::fillAvailablePortSettings() noexcept
{
  mEditor.fetchAvailablePortSettings();
}

}} // namespace Mdt{ namespace SerialPort{
