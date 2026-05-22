// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
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
   mWriter(&mSerialPort),
   mPinoutSignalsEventNotifier(&mSerialPort)
{
  mUi.setupUi(this);
  setCentralWidget(mCentralWidget);
  mCentralWidget->setFocusToCommandEdit();

  statusBar()->addWidget(mStatusLabel);
  statusBar()->addPermanentWidget(mPinoutSignalsWidget);

  connect(&mStateMachine, &MainWindowStateMachine::currentStateChanged, this, &MainWindow::setCurrentState);

  connect(mUi.actionConfigurePort, &QAction::triggered, this, &MainWindow::setupSerialPort);
  connect(mUi.actionOpenPort, &QAction::triggered, this, &MainWindow::openSerialPort);
  connect(mUi.actionClosePort, &QAction::triggered, this, &MainWindow::closeSerialPort);

  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::dataTerminalReadyChanged, mUi.actionSetDTR, &QAction::setChecked);
  connect(mUi.actionSetDTR, &QAction::triggered, this, &MainWindow::setDTR);

  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::requestToSendChanged, mUi.actionSetRTS, &QAction::setChecked);
  connect(mUi.actionSetRTS, &QAction::triggered, this, &MainWindow::setRTS);

  connect(&mPinoutSignalsUiController, &PinoutSignalsUiController::breakChanged, mUi.actionSetBreak, &QAction::setChecked);
  connect(mUi.actionSetBreak, &QAction::triggered, this, &MainWindow::setBreak);

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

  showPortClosedStatusMessage();
  mStateMachine.start();
}

void MainWindow::setCurrentState(const MainWindowState & state)
{
  mCentralWidget->setCurrentState(state);
  mUi.actionConfigurePort->setEnabled( state.canConfigurePort() );
  mUi.actionOpenPort->setEnabled( state.canOpenPort() );
  mUi.actionClosePort->setEnabled( state.canClosePort() );
  mUi.actionSetDTR->setEnabled( state.canSetDTR() );
  mUi.actionSetRTS->setEnabled( state.canSetRTS() && (mSerialPortSettings.flowControl() != QSerialPort::HardwareControl) );
  mUi.actionSetBreak->setEnabled( state.canSetBreak() );
  mUi.actionSendXON->setEnabled( state.canSendXON() );
  mUi.actionSendXOFF->setEnabled( state.canSendXOFF() );
}

void MainWindow::setupSerialPort()
{
  assert( !mSerialPort.isOpen() );

  Mdt::SerialPort::SettingsDialog dialog(this);

  dialog.setSettings(mSerialPortSettings);

  const int result = dialog.exec();
  if(result == QDialog::Accepted){
    mSerialPortSettings = dialog.buildSettings();
    mWriter.setSettings( mSerialPortSettings.sendByteByByteSettings() );
  }
}

bool MainWindow::hasSerialPortSettings() const
{
  if( !mSerialPortSettings.hasPortInfo() ){
    return false;
  }

  return true;
}

void MainWindow::openSerialPort()
{
  assert( !mSerialPort.isOpen() );

  if( !hasSerialPortSettings() ){
    setupSerialPort();
  }
  if( !hasSerialPortSettings() ){
    return;
  }

  Mdt::SerialPort::PortSetup ps;

  try{
    ps.fetchPortInformations( mSerialPortSettings.portInfo() );
  }catch(const Mdt::SerialPort::QRuntimeError & error){
    displayErrorMessage(
      tr("Error while initializing port setup: %1")
      .arg( error.text() )
    );
    return;
  }

  try{
    ps.configureInterfaceBeforeOpenPortIfRequired( mSerialPortSettings.interface() );
  }catch(const Mdt::SerialPort::QRuntimeError & error){
      displayErrorMessage(
        tr("Error while configuring interface for port %1 (before open)")
        .arg( mSerialPortSettings.portName() )
        , error.informativeText(), error.detailedText() );
      return;
  }

  ps.setSettingsToPort(mSerialPortSettings, mSerialPort);
  /// mSerialPort.setReadBufferSize(10);
  if( !mSerialPort.open(QIODevice::ReadWrite) ){
    /// \todo TODO: should be cleaner
    if(mSerialPort.error() == QSerialPort::PermissionError){
      const QString text = tr(
        "Open serial port %1 failed due to permission error."
      ).arg( mSerialPort.portName() );
      const QString informativeText = tr(
        "The device may already be locked by another program, or you don't have the permissions to open it.\n"
        "System reported: %1"
      ).arg( mSerialPort.errorString() );
      /// \todo Should only be displayed on Linux
      const QString linuxDetailedText = tr(
        "On Linux, like Ubuntu, you may not be in the dialout group. Maybe try:\n"
        "sudo adduser <user> dialout\n"
        "Then logoff and login again (your groups can be listed with the groups command)."
      );
      displayErrorMessage(text, informativeText, linuxDetailedText);
    }else{
      displayErrorMessage(
        tr("Error while open serial port %1. System reported: %2")
        .arg( mSerialPort.portName(), mSerialPort.errorString() )
      );
    }
    return;
  }

  try{
    ps.configureInterfaceOncePortOpenIfRequired(mSerialPortSettings.interface(), mSerialPort);
  }catch(const Mdt::SerialPort::QRuntimeError & error){
      displayErrorMessage( error.text(), error.informativeText(), error.detailedText() );
      mSerialPort.close();
      return;
  }

  connectOnSerialPortErrorOccured();

  mPinoutSignalsEventNotifier.setPortOpen();
  showPortOpenStatusMessage();
  mStateMachine.setPortOpenEvent();
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
  if(mSerialPort.error() == QSerialPort::NoError){
    setBreak(false);
  }

  mSerialPort.close();

  disconnectOnSerialPortErrorOccured();

  showPortClosedStatusMessage();
  mStateMachine.setPortClosedEvent();
}

void MainWindow::submitCommand(const QString & command)
{
  assert( mSerialPort.isOpen() );

  qDebug() << "submit command: " << command;

  // mCentralWidget->addTextToConsole(command);

  mWriter.write( command.toLocal8Bit() );

  /// \todo return value ?
  // mSerialPort.write( command.toLocal8Bit() );
}

/// \todo should use a text decoder
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

  /**
   * ASCII with ctl symbols
   * HEX
   *
   * Note: should use MdtPlainText
   *
   * Future:
   * Write and read original buffers
   */
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

void MainWindow::connectOnSerialPortErrorOccured()
{
  mOnSerialPortErrorOccuredConnection = connect(&mSerialPort, &QSerialPort::errorOccurred, this, &MainWindow::onSerialPortErrorOccured);
}

void MainWindow::disconnectOnSerialPortErrorOccured()
{
  disconnect(mOnSerialPortErrorOccuredConnection);
}

void MainWindow::onSerialPortErrorOccured(QSerialPort::SerialPortError error)
{
  if(error != QSerialPort::NoError){
    qDebug() << "serial port error: " << error;
    if(error == QSerialPort::ResourceError){
      /*
       * If, f.ex. and USB adapter has been plugged out,
       * this error will come again and again.
       * The best we can do is to close the port and display the error.
       * Also, when the user plugs the adapter again, it may have another port name.
       */
      closeSerialPort();
    }
    /** \todo
     * If unplug an USB device, several QSerialPort::ReadError will be emitted.
     * This is a bug in PinoutSignalsEventNotifier.
     * https://gitlab.com/scandyna/mdtterminal/-/issues/5
     */
    displayErrorMessage(
      tr("Unexpected serial port error occured: %1")
      .arg( mSerialPort.errorString() )
    );
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

void MainWindow::displayErrorMessage(const QString & text, const QString & informativeText, const QString & detailedText)
{
  QMessageBox msgBox(this);
  msgBox.setWindowTitle( tr("Error") );
  msgBox.setIcon(QMessageBox::Critical);
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.setText(text);
  if( !informativeText.isEmpty() ){
    msgBox.setInformativeText(informativeText);
  }
  if( !detailedText.isEmpty() ){
    msgBox.setDetailedText(detailedText);
  }
  msgBox.exec();

  // QMessageBox::critical(this, tr("Error"), text);
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
