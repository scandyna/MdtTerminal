// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SettingsBuilder.h"
#include "Mdt/SerialPort/TestLib/TestPortInfo.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include <chrono>

using namespace Mdt::SerialPort;
using Mdt::SerialPort::TestLib::TestPortInfo;
using namespace std::chrono_literals;


TEST_CASE("settingsFromRawData")
{
  SettingsRawData data;

  data.portInfo = TestPortInfo::fromPortNameAndSystemLocation("ttyS1", "/dev/ttyS1");
  data.baudRate = 4800;
  data.dataBits = QSerialPort::Data6;
  data.parity = QSerialPort::SpaceParity;
  data.flowControl = QSerialPort::SoftwareControl;
  data.stopBits = QSerialPort::TwoStop;
  data.interface = Interface::fromStandardAndParameterValue(InterfaceStandard::RS_422, 1);
  data.sendByteByByteIsEnabled = true;
  data.sendByteByByteIntervalInMilliseconds = 50;

  const Settings settings = SettingsBuilder::settingsFromRawData(data);

  CHECK( settings.portName() == "ttyS1" );
  CHECK( settings.baudRate() == 4800 );
  CHECK( settings.dataBits() == QSerialPort::Data6 );
  CHECK( settings.parity() == QSerialPort::SpaceParity );
  CHECK( settings.flowControl() == QSerialPort::SoftwareControl );
  CHECK( settings.stopBits() == QSerialPort::TwoStop );
  CHECK( settings.interfaceStandard() == InterfaceStandard::RS_422 );
  CHECK( settings.sendByteByByteIsEnabled() );
  CHECK( settings.sendByteByByteInterval() == 50ms );
}
