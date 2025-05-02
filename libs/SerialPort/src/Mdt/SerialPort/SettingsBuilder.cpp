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
#include "SendByteByByteSettings.h"

namespace Mdt{ namespace SerialPort{

Settings SettingsBuilder::settingsFromRawData(const SettingsRawData & data)
{
  SettingsValidation::validateSettings(data);

  Settings settings;

  settings.setPortName(data.portName);
  settings.setBaudRate(data.baudRate);
  settings.setDataBits(data.dataBits);
  settings.setParity(data.parity);
  settings.setFlowControl(data.flowControl);
  settings.setStopBits(data.stopBits);
  settings.setInterface(data.interface);

  if( data.sendByteByByteIsEnabled ){
    settings.setSendByteByByteSettings( SendByteByByteSettings::enabledWithRawIntervalInMilliseconds(data.sendByteByByteIntervalInMilliseconds) );
  }else{
    settings.setSendByteByByteSettings( SendByteByByteSettings::disabled() );
  }

  return settings;
}

}} // namespace Mdt{ namespace SerialPort{
