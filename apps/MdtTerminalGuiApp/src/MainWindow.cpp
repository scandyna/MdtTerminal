// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "MainWindow.h"
#include "Mdt/SerialPort/SettingsDialog.h"
#include "Mdt/SerialPort/PortSetup.h"
#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
 : QMainWindow(parent),
   mCentralWidget(new CentralWidget),
   mSerialPortSettings( Mdt::SerialPort::Settings::defaultSettings() )
{
  mUi.setupUi(this);
  setCentralWidget(mCentralWidget);
  mCentralWidget->setFocusToCommandEdit();

  connect(mUi.actionConfigurePort, &QAction::triggered, this, &MainWindow::setupSerialPort);
  connect(mUi.actionOpenPort, &QAction::triggered, this, &MainWindow::openSerialPort);
  connect(mUi.actionClosePort, &QAction::triggered, this, &MainWindow::closeSerialPort);
}

void MainWindow::setupSerialPort()
{
  /// \todo What if port is open ?

  Mdt::SerialPort::SettingsDialog dialog(this);

  dialog.setSettings(mSerialPortSettings);

  const int result = dialog.exec();
  if(result == QDialog::Accepted){
    mSerialPortSettings = dialog.buildSettings();
  }
}

void MainWindow::openSerialPort()
{
  /// \todo What if port is open ?

  Mdt::SerialPort::PortSetup::setSettingsToPort(mSerialPortSettings, mSerialPort);
  if( !mSerialPort.open(QIODevice::ReadWrite) ){
    displayErrorMessage( tr("Error while open serial port: %1").arg( mSerialPort.errorString() ) );
  }
}

void MainWindow::closeSerialPort()
{
  if( mSerialPort.isOpen() ){
    mSerialPort.close();
  }
}

void MainWindow::displayErrorMessage(const QString & message)
{
  QMessageBox::critical(this, tr("Error"), message);
}
