// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortSetup.h"
#include "SettingsRawData.h"
#include "SettingsBuilder.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

void PortSetup::setSettingsToPort(const Settings & settings, QSerialPort & port)
{
  assert( !port.isOpen() );

  port.setPortName( settings.portName() );
  port.setBaudRate( settings.baudRate() );
  port.setDataBits( settings.dataBits() );
  port.setParity( settings.parity() );
  port.setStopBits( settings.stopBits() );
  port.setFlowControl( settings.flowControl() );
}

Settings PortSetup::getSettingsFromPort(const QSerialPort & port)
{
  SettingsRawData data;

  data.portName = port.portName();
  data.baudRate = port.baudRate();
  data.dataBits = port.dataBits();
  data.parity = port.parity();
  data.stopBits = port.stopBits();
  data.flowControl = port.flowControl();

  return SettingsBuilder::settingsFromRawData(data);
}

}} // namespace Mdt{ namespace SerialPort{
