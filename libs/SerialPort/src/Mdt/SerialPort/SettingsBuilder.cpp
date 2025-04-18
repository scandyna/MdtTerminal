// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
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
  settings.setFlowControl(data.flowControl);
  settings.setStopBits(data.stopBits);
  settings.setInterfaceStandard(data.interfaceStandard);

  return settings;
}

}} // namespace Mdt{ namespace SerialPort{
