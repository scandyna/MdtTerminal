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

#include "Mdt/SerialPort/Settings.h"
#include "Mdt/SerialPort/PinoutSignalsEventNotifier.h"
#include "Mdt/SerialPort/PinoutSignalsUiController.h"
#include "Mdt/SerialPort/PinoutSignalsWidget.h"
#include "Mdt/SerialPort/Writer.h"
#include "ui_MainWindow.h"
#include "MainWindowState.h"
#include "MainWindowStateMachine.h"
#include "CentralWidget.h"
#include <QMainWindow>
#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
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
  void displayErrorMessage(const QString & message);

  void showPortOpenStatusMessage();
  void showPortClosedStatusMessage();

  Ui::MainWindow mUi;
  CentralWidget *mCentralWidget;
  QLabel *mStatusLabel;
  Mdt::SerialPort::PinoutSignalsWidget *mPinoutSignalsWidget;
  Mdt::SerialPort::Settings mSerialPortSettings;
  QSerialPort mSerialPort;
  Mdt::SerialPort::Writer mWriter;
  QSerialPortInfo mSerialPortInfo;
  Mdt::SerialPort::PinoutSignalsEventNotifier mPinoutSignalsEventNotifier;
  Mdt::SerialPort::PinoutSignalsUiController mPinoutSignalsUiController;
  MainWindowStateMachine mStateMachine;
  QMetaObject::Connection mOnSerialPortErrorOccuredConnection;
};

#endif // #ifndef MAIN_WINDOW_H
