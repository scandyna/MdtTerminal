// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "CentralWidget.h"

CentralWidget::CentralWidget(QWidget *parent)
 : QWidget(parent)
{
  mUi.setupUi(this);
}

void CentralWidget::setFocusToCommandEdit()
{
  mUi.commandEdit->setFocus();
}
