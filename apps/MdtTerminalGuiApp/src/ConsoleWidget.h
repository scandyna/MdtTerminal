// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef CONSOLE_WIDGET_H
#define CONSOLE_WIDGET_H

#include <QPlainTextEdit>

/*! \brief Console widget
 */
class ConsoleWidget : public QPlainTextEdit
{
  Q_OBJECT

 public:

  /*! \brief Constructor
   */
  explicit
  ConsoleWidget(QWidget *parent = nullptr);
};

#endif // #ifndef CONSOLE_WIDGET_H
