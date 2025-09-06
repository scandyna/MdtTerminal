// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef CENTRAL_WIDGET_H
#define CENTRAL_WIDGET_H

#include "ui_CentralWidget.h"
#include <QWidget>
#include <QString>

/*! \brief Central widget of the application
 */
class CentralWidget : public QWidget
{
  Q_OBJECT

 public:

  /*! \brief Constructor
   */
  explicit
  CentralWidget(QWidget *parent = nullptr);

  /*! \brief Set the focus to the command edit
   */
  void setFocusToCommandEdit();

 public slots:

  /*! \brief Add text to the console
   */
  void addTextToConsole(const QString & text);

 signals:

  /*! \brief Emitted when user requested to send a command
   */
  void sendCommandRequested(const QString & command);

 private slots:

  void requestSendCommand();

 private:

  Ui::CentralWidget mUi;
};

#endif // #ifndef CENTRAL_WIDGET_H
