// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsEditor.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

SettingsEditor::SettingsEditor(QObject* parent)
 : AbstractSettingsEditor(parent)
{
}

}} // namespace Mdt{ namespace SerialPort{
