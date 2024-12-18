// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui_MainWindow.h"
#include "CentralWidget.h"
#include <QMainWindow>
#include <QWidget>

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

 private:

  Ui::MainWindow mUi;
  CentralWidget *mCentralWidget;
};

#endif // #ifndef MAIN_WINDOW_H
