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
#include "Mdt/SerialPort/QRuntimeError.h"
#include <QAction>
#include <QStatusBar>
#include <QMessageBox>
#include <optional>
#include <cassert>

// #include <QDebug>

using namespace Mdt::SerialPort;


/// \todo Add about Qt: https://doc.qt.io/qt-6/qmessagebox.html#aboutQt

MainWindow::MainWindow(QWidget* parent)
 : QMainWindow(parent),
   mCentralWidget(new CentralWidget),
   mStatusLabel(new QLabel),
   mPinoutSignalsWidget(new Mdt::SerialPort::PinoutSignalsWidget)
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

  connect(&mSerialPort, &SerialPort::readyRead, this, &MainWindow::readFromPort);

  mSerialPort.setPinoutSignalsEventNotifierEnabled(true);
  connect(&mSerialPort, &SerialPort::aboutToClose, &mPinoutSignalsUiController, &PinoutSignalsUiController::setAboutToCloseEvent);
  connect(&mSerialPort, &SerialPort::pinoutSignalsChanged, &mPinoutSignalsUiController, &PinoutSignalsUiController::setSignals);

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
  mUi.actionSetRTS->setEnabled( state.canSetRTS() && (mSerialPort.settings().flowControl() != QSerialPort::HardwareControl) );
  mUi.actionSetBreak->setEnabled( state.canSetBreak() );
  mUi.actionSendXON->setEnabled( state.canSendXON() );
  mUi.actionSendXOFF->setEnabled( state.canSendXOFF() );
}

void MainWindow::setupSerialPort()
{
  assert( !mSerialPort.isOpen() );

  Mdt::SerialPort::SettingsDialog dialog(this);

  dialog.setSettings( mSerialPort.settings() );

  const int result = dialog.exec();
  if(result == QDialog::Accepted){
    mSerialPort.setSettings( dialog.buildSettings() );
  }
}

bool MainWindow::hasSerialPortSettings() const
{
  return mSerialPort.hasRequiredSettings();
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

  try{
    mSerialPort.openReadWrite();
  }catch(const Mdt::SerialPort::PortOpenError & error){
    displayError(error);
    return;
  }

  connectOnSerialPortErrorOccured();
  showPortOpenStatusMessage();
  mStateMachine.setPortOpenEvent();
}

void MainWindow::closeSerialPort()
{
  mSerialPort.close();

  disconnectOnSerialPortErrorOccured();
  showPortClosedStatusMessage();
  mStateMachine.setPortClosedEvent();
}

/// \todo should use a text encoder
void MainWindow::submitCommand(const QString & command)
{
  assert( mSerialPort.isOpen() );

  const QByteArray data = command.toLocal8Bit();
  const qsizetype written = mSerialPort.write(data);
  if( written < data.size() ){
    const QString text = tr("Failed to write all data to port %1.\n"
                            "Error: %2")
                         .arg( mSerialPort.portName(), mSerialPort.errorString() );
    displayErrorMessage(text);
    return;
  }
}

/// \todo should use a text decoder
void MainWindow::readFromPort()
{
  assert( mSerialPort.isOpen() );

  QByteArray data = mSerialPort.readAll();
  if(data.isEmpty() && mSerialPort.error() != QSerialPort::NoError){
    QString text = tr("reading from port %1 failed.\nsystem returned: %2")
                   .arg( mSerialPort.portName(), mSerialPort.errorString() );
    displayErrorMessage(text);
    return;
  }

  // for(char c : data){
  //   qDebug() << "0x" << QString::number(c, 16);
  //   if(c == 0){
  //     qDebug() << "ZERO  0";
  //   }
  // }

  mCentralWidget->addTextToConsole( QString::fromLocal8Bit(data) );

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
  mOnSerialPortErrorOccuredConnection = connect(&mSerialPort, &SerialPort::errorOccurred, this, &MainWindow::onSerialPortErrorOccured);
}

void MainWindow::disconnectOnSerialPortErrorOccured()
{
  disconnect(mOnSerialPortErrorOccuredConnection);
}

void MainWindow::onSerialPortErrorOccured(QSerialPort::SerialPortError error)
{
  if(error == QSerialPort::NoError){
    return;
  }

  QString serialPortErrorString = mSerialPort.errorString();

  if(error == QSerialPort::ResourceError){
    /*
     * This error can occur when using an usb-serial adapter,
     * and it has been unplugged.
     * Once plugged in again, the system could map it to another serial port
     * (like ttyUSB0 -> ttyUSB2, COM3 -> COM5).
     * The best we can do is probably to close the port and show an error to the user.
     */
    closeSerialPort();
    QString text = tr("The port %1 is no more available.").arg( mSerialPort.portName() );
    QString informativeText = tr("The port is probably an usb-serial adapter that has been unplugged.");
    QString detailedText = tr("System returned: %1").arg(serialPortErrorString);
    displayErrorMessage(text, informativeText, detailedText);
    return;
  }

  // We don't know how to handle other errors yet.
  closeSerialPort();
  QString text = tr("An unexpected error occurred.");
  QString informativeText = tr("System returned: %1").arg(serialPortErrorString);
  displayErrorMessage(text, informativeText);
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
  /// \todo Should not use exec() !
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
}

void MainWindow::displayError(const Mdt::SerialPort::QRuntimeError & error)
{
  displayErrorMessage( error.text(), error.informativeText(), error.detailedText() );
}

void MainWindow::showPortOpenStatusMessage()
{
  showStatusMessage(
    tr("Port open: %1 %2 %3")
    .arg( mSerialPort.portName() )
    .arg( Mdt::SerialPort::SettingsStringFormat::baudeRateAndDpsStringFromSettings( mSerialPort.settings() ) )
    .arg( Mdt::SerialPort::FlowControlStringFormat::flowControlToShortString( mSerialPort.flowControl() ) )
  );
}

void MainWindow::showPortClosedStatusMessage()
{
  showStatusMessage( tr("Port closed") );
}
