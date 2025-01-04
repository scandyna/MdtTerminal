// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SettingsBuilder.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("settingsFromRawData")
{
  SettingsRawData data;

  data.baudRate = 4800;
  data.dataBits = QSerialPort::Data6;
  data.parity = QSerialPort::SpaceParity;
  data.flowControl = QSerialPort::SoftwareControl;

  const Settings settings = SettingsBuilder::settingsFromRawData(data);

  CHECK( settings.baudRate() == 4800 );
  CHECK( settings.dataBits() == QSerialPort::Data6 );
  CHECK( settings.parity() == QSerialPort::SpaceParity );
  CHECK( settings.flowControl() == QSerialPort::SoftwareControl );
}
