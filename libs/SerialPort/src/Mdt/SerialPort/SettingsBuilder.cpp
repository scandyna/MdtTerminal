// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsBuilder.h"
#include "SettingsValidation.h"

namespace Mdt{ namespace SerialPort{

Settings SettingsBuilder::settingsFromRawData(const SettingsRawData & data)
{
  SettingsValidation::validateSettings(data);

  Settings settings;

  settings.setBaudRate(data.baudRate);
  settings.setDataBits(data.dataBits);
  settings.setParity(data.parity);

  return settings;
}

}} // namespace Mdt{ namespace SerialPort{
