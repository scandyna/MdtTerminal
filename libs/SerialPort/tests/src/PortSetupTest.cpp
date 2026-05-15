// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PortSetup.h"
#include "Mdt/SerialPort/SettingsRawData.h"
#include "Mdt/SerialPort/SettingsBuilder.h"
#include "Mdt/SerialPort/TestLib/TestPortInfo.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::SerialPort::TestLib::TestPortInfo;


TEST_CASE("setSettingsToPort")
{
  QSerialPort port;

  SettingsRawData settingsData;
  settingsData.portInfo = TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0");
  settingsData.baudRate = 4800;
  settingsData.dataBits = QSerialPort::Data6;
  settingsData.parity = QSerialPort::MarkParity;
  settingsData.flowControl = QSerialPort::HardwareControl;
  settingsData.stopBits = QSerialPort::TwoStop;

  const Settings settings = SettingsBuilder::settingsFromRawData(settingsData);

  PortSetup::setSettingsToPort(settings, port);

  CHECK( port.portName() == "ttyS0" );
  CHECK( port.baudRate() == 4800 );
  CHECK( port.dataBits() == QSerialPort::Data6 );
  CHECK( port.parity() == QSerialPort::MarkParity );
  CHECK( port.flowControl() == QSerialPort::HardwareControl );
  CHECK( port.stopBits() == QSerialPort::TwoStop );
}

TEST_CASE("getSettingsFromPort")
{
  QSerialPort port;

  port.setPortName("ttyS1");
  port.setBaudRate(4800);
  port.setDataBits(QSerialPort::Data6);
  port.setParity(QSerialPort::MarkParity);
  port.setFlowControl(QSerialPort::HardwareControl);
  port.setStopBits(QSerialPort::TwoStop);

  const Settings settings = PortSetup::getSettingsFromPort(port);

  CHECK( settings.portName() == "ttyS1" );
  CHECK( settings.baudRate() == 4800 );
  CHECK( settings.dataBits() == QSerialPort::Data6 );
  CHECK( settings.parity() == QSerialPort::MarkParity );
  CHECK( settings.flowControl() == QSerialPort::HardwareControl );
  CHECK( settings.stopBits() == QSerialPort::TwoStop );
}
