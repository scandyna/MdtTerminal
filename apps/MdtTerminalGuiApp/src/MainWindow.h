// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "Mdt/SerialPort/SerialPort.h"
#include "Mdt/SerialPort/PinoutSignalsUiController.h"
#include "Mdt/SerialPort/PinoutSignalsWidget.h"
#include "Mdt/SerialPort/QRuntimeError.h"
#include "ui_MainWindow.h"
#include "MainWindowState.h"
#include "MainWindowStateMachine.h"
#include "CentralWidget.h"
#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QLabel>

/*! \brief Main windows of MdtTerminalGuiApp
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:

  /*! \brief Constructor
   */
  explicit
  MainWindow(QWidget *parent = nullptr);

 private slots:

  void setCurrentState(const MainWindowState & state);

  void setupSerialPort();

  bool hasSerialPortSettings() const;

  void openSerialPort();
  void closeSerialPort();

  void submitCommand(const QString & command);
  void readFromPort();

  void setDTR(bool on);
  void setRTS(bool on);
  void setBreak(bool on);

  void sendXON();
  void sendXOFF();

  void connectOnSerialPortErrorOccured();
  void disconnectOnSerialPortErrorOccured();
  void onSerialPortErrorOccured(QSerialPort::SerialPortError error);

 private:

  void sendAsciiControl(char c);

  void showStatusMessage(const QString &message);
  void displayErrorMessage( const QString & text, const QString & informativeText = QString(), const QString & detailedText = QString() );
  void displayError(const Mdt::SerialPort::QRuntimeError & error);

  void showPortOpenStatusMessage();
  void showPortClosedStatusMessage();

  Ui::MainWindow mUi;
  CentralWidget *mCentralWidget;
  QLabel *mStatusLabel;
  Mdt::SerialPort::PinoutSignalsWidget *mPinoutSignalsWidget;
  Mdt::SerialPort::SerialPort mSerialPort;
  Mdt::SerialPort::PinoutSignalsUiController mPinoutSignalsUiController;
  MainWindowStateMachine mStateMachine;
  QMetaObject::Connection mOnSerialPortErrorOccuredConnection;
};

#endif // #ifndef MAIN_WINDOW_H
