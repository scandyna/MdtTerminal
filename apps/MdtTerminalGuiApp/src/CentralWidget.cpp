// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "CentralWidget.h"
#include <QPushButton>

CentralWidget::CentralWidget(QWidget *parent)
 : QWidget(parent)
{
  mUi.setupUi(this);

  connect(mUi.sendCommandButton, &QPushButton::clicked, this, &CentralWidget::requestSendCommand);
}

void CentralWidget::setFocusToCommandEdit()
{
  mUi.commandEdit->setFocus();
}

void CentralWidget::addTextToConsole(const QString & text)
{
  mUi.console->appendPlainText(text);
}

void CentralWidget::requestSendCommand()
{
  emit sendCommandRequested( mUi.commandEdit->text() );
}
