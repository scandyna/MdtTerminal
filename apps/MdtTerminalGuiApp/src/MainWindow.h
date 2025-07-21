// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "Mdt/SerialPort/Settings.h"
#include "ui_MainWindow.h"
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

  void setupSerialPort();

  void openSerialPort();
  void closeSerialPort();

 private:

  void showStatusMessage(const QString &message);
  void displayErrorMessage(const QString & message);

  void showPortOpenStatusMessage();
  void showPortClosedStatusMessage();

  Ui::MainWindow mUi;
  CentralWidget *mCentralWidget;
  QLabel *mStatusLabel;
  Mdt::SerialPort::Settings mSerialPortSettings;
  QSerialPort mSerialPort;
  QSerialPortInfo mSerialPortInfo;
};

#endif // #ifndef MAIN_WINDOW_H
