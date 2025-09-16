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
#include "Mdt/SerialPort/SettingsStringFormat.h"
#include "Mdt/SerialPort/FlowControlStringFormat.h"
#include "Mdt/SerialPort/PortSetup.h"
#include "Mdt/SerialPort/QRuntimeError.h"
#include <QAction>
#include <QStatusBar>
#include <QMessageBox>
#include <optional>
#include <cassert>

#include <QDebug>

using namespace Mdt::SerialPort;


MainWindow::MainWindow(QWidget* parent)
 : QMainWindow(parent),
   mCentralWidget(new CentralWidget),
   mStatusLabel(new QLabel),
   mPinoutSignalsWidget(new Mdt::SerialPort::PinoutSignalsWidget),
   mSerialPortSettings( Mdt::SerialPort::Settings::defaultSettings() ),
   mPinoutSignalsEventNotifier(&mSerialPort)
{
  mUi.setupUi(this);
  setCentralWidget(mCentralWidget);
  mCentralWidget->setFocusToCommandEdit();

  statusBar()->addWidget(mStatusLabel);
  statusBar()->addPermanentWidget(mPinoutSignalsWidget);

  connect(mUi.actionConfigurePort, &QAction::triggered, this, &MainWindow::setupSerialPort);
  connect(mUi.actionOpenPort, &QAction::triggered, this, &MainWindow::openSerialPort);
  connect(mUi.actionClosePort, &QAction::triggered, this, &MainWindow::closeSerialPort);

  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::dataTerminalReadyChanged, mUi.actionSetDTR, &QAction::setChecked);
  connect(mUi.actionSetDTR, &QAction::triggered, this, &MainWindow::setDTR);

  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::requestToSendChanged, mUi.actionSetRTS, &QAction::setChecked);
  connect(mUi.actionSetRTS, &QAction::triggered, this, &MainWindow::setRTS);

  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::breakChanged, mUi.actionSetBreak, &QAction::setChecked);
  connect(mUi.actionSetBreak, &QAction::triggered, this, &MainWindow::setBreak);

  connect(mUi.actionsandbox, &QAction::triggered, this, &MainWindow::sandboxCommand);

  connect(mUi.actionSendXON, &QAction::triggered, this, &MainWindow::sendXON);
  connect(mUi.actionSendXOFF, &QAction::triggered, this, &MainWindow::sendXOFF);

  connect(mCentralWidget, &CentralWidget::sendCommandRequested, this, &MainWindow::submitCommand);

  connect(&mSerialPort, &QSerialPort::readyRead, this, &MainWindow::readFromPort);

  connect(&mSerialPort, &QSerialPort::aboutToClose, &mPinoutSignalsUiController, &PinoutSignalsUiController::setAboutToCloseEvent);
  connect(&mPinoutSignalsEventNotifier, &PinoutSignalsEventNotifier::signalsChanged, &mPinoutSignalsUiController, &PinoutSignalsUiController::setSignals);

  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::receiveDataChanged, mPinoutSignalsWidget, &PinoutSignalsWidget::setReceiveDataOn);
  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::transmitDataChanged, mPinoutSignalsWidget, &PinoutSignalsWidget::setTransmitDataOn);
  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::requestToSendChanged, mPinoutSignalsWidget, &PinoutSignalsWidget::setRequestToSendOn);
  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::clearToSendChanged, mPinoutSignalsWidget, &PinoutSignalsWidget::setClearToSendOn);
  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::dataCarrierDetectChanged, mPinoutSignalsWidget, &PinoutSignalsWidget::setDataCarrierDetectOn);
  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::dataSetReadyChanged, mPinoutSignalsWidget, &PinoutSignalsWidget::setDataSetReadyOn);
  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::dataTerminalReadyChanged, mPinoutSignalsWidget, &PinoutSignalsWidget::setDataTerminalReadyOn);
  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::ringIndicatorChanged, mPinoutSignalsWidget, &PinoutSignalsWidget::setRingIndicatorOn);
  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::breakChanged, mPinoutSignalsWidget, &PinoutSignalsWidget::setBreakOn);

  connect(&mSerialPort, &QSerialPort::errorOccurred, this, &MainWindow::onSerialPortErrorOccured);

  showPortClosedStatusMessage();
}

void MainWindow::setupSerialPort()
{
  /// \todo What if port is open ?

  Mdt::SerialPort::SettingsDialog dialog(this);

  /// \todo Should we set current port info ? Think yes
  
  dialog.setSettings(mSerialPortSettings);

  const int result = dialog.exec();
  if(result == QDialog::Accepted){
    mSerialPortSettings = dialog.buildSettings();
    mSerialPortInfo = dialog.currentPortInfo();
  }
}

void MainWindow::openSerialPort()
{
  /// \todo If no port has been selected, open settings dialog ?

  /// \todo What if port is open ? - Precondition: GUI must be coherent

  const bool shouldConfigureInterface = mSerialPortSettings.interface().isConfigurable();

  std::optional<Mdt::SerialPort::PortSetup> ps;
  try{
    ps.emplace(mSerialPortInfo);
  }catch(const Mdt::SerialPort::QRuntimeError & error){
    displayErrorMessage( error.text() );
    return;
  }
  assert( ps.has_value() );
  ps->setSettingsToPort(mSerialPortSettings, mSerialPort);

  const bool shouldConfigureInterfaceBeforeOpenPort = shouldConfigureInterface && ps->shouldConfigureInterfaceBeforeOpenPort();
  const bool shouldConfigureInterfaceOncePortOpen = shouldConfigureInterface && !shouldConfigureInterfaceBeforeOpenPort;

  if(shouldConfigureInterfaceBeforeOpenPort){
    try{
      ps->configureInterfaceBeforeOpenPort( mSerialPortSettings.interface() );
    }catch(const Mdt::SerialPort::QRuntimeError & error){
      displayErrorMessage( error.text() );
      return;
    }
  }

  Mdt::SerialPort::PortSetup::setSettingsToPort(mSerialPortSettings, mSerialPort);
  /// mSerialPort.setReadBufferSize(10);
  if( !mSerialPort.open(QIODevice::ReadWrite) ){
    displayErrorMessage( tr("Error while open serial port: %1").arg( mSerialPort.errorString() ) );
    return;
  }

  if(shouldConfigureInterfaceOncePortOpen){
    try{
      ps->configureInterfaceOncePortOpen(mSerialPortSettings.interface(), mSerialPort);
    }catch(const Mdt::SerialPort::QRuntimeError & error){
      displayErrorMessage( error.text() );
      mSerialPort.close();
      return;
    }
  }

  mPinoutSignalsEventNotifier.setPortOpen();
  showPortOpenStatusMessage();
}

void MainWindow::closeSerialPort()
{
  if( !mSerialPort.isOpen() ){
    return;
  }

  /*
   * Some drivers/devices, like Moxa UPort Linux,
   * do not cancel break.
   */
  setBreak(false);

  mSerialPort.close();

  showPortClosedStatusMessage();
}

void MainWindow::submitCommand(const QString & command)
{
  assert( mSerialPort.isOpen() );

  qDebug() << "submit command: " << command;

  // mCentralWidget->addTextToConsole(command);

  /// \todo return value ?
  mSerialPort.write( command.toLocal8Bit() );
}

void MainWindow::readFromPort()
{
  assert( mSerialPort.isOpen() );

  /// \todo sandboxing

  QByteArray data = mSerialPort.readAll();
  for(char c : data){
    qDebug() << "0x" << QString::number(c, 16);
    if(c == 0){
      qDebug() << "ZERO  0";
    }
  }

  mCentralWidget->addTextToConsole( QString::fromLocal8Bit(data) );

  /// mCentralWidget->addTextToConsole( QString::fromLocal8Bit( mSerialPort.readAll() ) );
}

void MainWindow::setDTR(bool on)
{
  assert( mSerialPort.isOpen() );

  if( !mSerialPort.setDataTerminalReady(on) ){
    displayErrorMessage( mSerialPort.errorString() );
  }
}

void MainWindow::setRTS(bool on)
{
  assert( mSerialPort.isOpen() );

  if( !mSerialPort.setRequestToSend(on) ){
    displayErrorMessage( mSerialPort.errorString() );
  }
}

void MainWindow::setBreak(bool on)
{
  assert( mSerialPort.isOpen() );

  if( !mSerialPort.setBreakEnabled(on) ){
    displayErrorMessage( mSerialPort.errorString() );
  }
}

void MainWindow::sandboxCommand()
{
  qDebug() << "sanboxCommand() ..";

  // const QChar data[2] = {0x0011, 0x0013};
  // 
  // mCentralWidget->addTextToConsole( QString(data, 2) );
  // 
  // // mCentralWidget->addTextToConsole( QChar(0x2411) );
  // // mCentralWidget->addTextToConsole( QChar::fromLatin1(0x13) );
  // // mCentralWidget->addTextToConsole( QChar::fromLatin1(0x21) );
  // 
  // return;

  assert( mSerialPort.isOpen() );

  // mSerialPort.write( QByteArray(1, 0x11) );
  // 
  // return;
  // 
  // qDebug() << "setBreakEnabled..";
  // if( !mSerialPort.setBreakEnabled(false) ){
  //   displayErrorMessage( mSerialPort.errorString() );
  // }
}

void MainWindow::sendXON()
{
  assert( mSerialPort.isOpen() );

  sendAsciiControl(0x11);
}

void MainWindow::sendXOFF()
{
  assert( mSerialPort.isOpen() );

  sendAsciiControl(0x13);
}

void MainWindow::onSerialPortErrorOccured(QSerialPort::SerialPortError error)
{
  if(error != QSerialPort::NoError){
   displayErrorMessage( mSerialPort.errorString() );
  }
}

void MainWindow::sendAsciiControl(char c)
{
  assert( mSerialPort.isOpen() );

  /// \todo return value ?
  mSerialPort.write( QByteArray(1, c) );
}

void MainWindow::showStatusMessage(const QString &message)
{
  mStatusLabel->setText(message);
}

void MainWindow::displayErrorMessage(const QString & message)
{
  QMessageBox::critical(this, tr("Error"), message);
}

void MainWindow::showPortOpenStatusMessage()
{
  showStatusMessage(
    tr("Port open: %1 %2 %3")
    .arg( mSerialPort.portName() )
    .arg( Mdt::SerialPort::SettingsStringFormat::baudeRateAndDpsStringFromPort(mSerialPort) )
    .arg( Mdt::SerialPort::FlowControlStringFormat::flowControlToShortString( mSerialPort.flowControl() ) )
  );
}

void MainWindow::showPortClosedStatusMessage()
{
  showStatusMessage( tr("Port closed") );
}
