// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "MainWindow.h"
#include "Mdt/SerialPort/SettingsDialog.h"
#include <QAction>

MainWindow::MainWindow(QWidget* parent)
 : QMainWindow(parent),
   mCentralWidget(new CentralWidget)
{
  mUi.setupUi(this);
  setCentralWidget(mCentralWidget);
  mCentralWidget->setFocusToCommandEdit();

  connect(mUi.actionConfigurePort, &QAction::triggered, this, &MainWindow::setupSerialPort);
}

void MainWindow::setupSerialPort()
{
  Mdt::SerialPort::SettingsDialog dialog(this);

  dialog.setSettings( Mdt::SerialPort::Settings::defaultSettings() );

  dialog.exec();
}
