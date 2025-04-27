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
#include <QString>

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

  void displayErrorMessage(const QString & message);

  Ui::MainWindow mUi;
  CentralWidget *mCentralWidget;
  Mdt::SerialPort::Settings mSerialPortSettings;
  QSerialPort mSerialPort;
};

#endif // #ifndef MAIN_WINDOW_H
