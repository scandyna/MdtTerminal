// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
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

  fetchAvailablePorts();
  fillAvailablePortSettings();
}

SettingsDialog::~SettingsDialog() noexcept = default;

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
  fillAvailableBaudRates();
  fillAvailableDataBits();
  fillAvailableParities();
  fillAvailableStopBits();
  fillAvailableFlowControls();
}

void SettingsDialog::fillAvailableBaudRates() noexcept
{
  mUi->baudRateBox->addItem(QLatin1String("4800"), QSerialPort::Baud4800);
  mUi->baudRateBox->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
}

void SettingsDialog::fillAvailableDataBits() noexcept
{
  mUi->dataBitsBox->addItem(QLatin1String("5"), QSerialPort::Data5);
  mUi->dataBitsBox->addItem(QLatin1String("6"), QSerialPort::Data6);
  mUi->dataBitsBox->addItem(QLatin1String("7"), QSerialPort::Data7);
  mUi->dataBitsBox->addItem(QLatin1String("8"), QSerialPort::Data8);
}

void SettingsDialog::fillAvailableParities() noexcept
{
  mUi->parityBox->addItem(tr("None"), QSerialPort::NoParity);
  mUi->parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
  mUi->parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
  mUi->parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
  mUi->parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);
}

void SettingsDialog::fillAvailableStopBits() noexcept
{
  mUi->stopBitsBox->addItem(QLatin1String("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
  mUi->stopBitsBox->addItem(QLatin1String("1.5"), QSerialPort::OneAndHalfStop);
#endif
  mUi->stopBitsBox->addItem(QLatin1String("2"), QSerialPort::TwoStop);
}

void SettingsDialog::fillAvailableFlowControls() noexcept
{
  mUi->flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
  mUi->flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
  mUi->flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

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
