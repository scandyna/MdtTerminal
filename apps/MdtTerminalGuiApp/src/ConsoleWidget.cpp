// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(QWidget* parent)
 : QPlainTextEdit(parent)
{
  setReadOnly(true);
  setCenterOnScroll(true);
}
