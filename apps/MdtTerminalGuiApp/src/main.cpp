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
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}