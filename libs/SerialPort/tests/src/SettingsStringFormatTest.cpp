// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SettingsStringFormat.h"
#include "Mdt/SerialPort/SettingsRawData.h"
#include "Mdt/SerialPort/SettingsBuilder.h"
#include <QSerialPort>
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("dpsStringFromSettings")
{
  SettingsRawData data;
  data.portName = "ttyS0";
  data.baudRate = 9600;
  data.flowControl = QSerialPort::NoFlowControl;

  SECTION("8-N-1")
  {
    data.dataBits = QSerialPort::Data8;
    data.parity = QSerialPort::NoParity;
    data.stopBits = QSerialPort::OneStop;
    const Settings settings = SettingsBuilder::settingsFromRawData(data);

    CHECK( SettingsStringFormat::dpsStringFromSettings(settings) == "8-N-1" );
  }

  SECTION("7-E-1")
  {
    data.dataBits = QSerialPort::Data7;
    data.parity = QSerialPort::EvenParity;
    data.stopBits = QSerialPort::OneStop;
    const Settings settings = SettingsBuilder::settingsFromRawData(data);

    CHECK( SettingsStringFormat::dpsStringFromSettings(settings) == "7-E-1" );
  }
}

TEST_CASE("dpsStringFromPort")
{
  QSerialPort port;
  port.setPortName("ttyS0");

  SECTION("8-N-1")
  {
    port.setDataBits(QSerialPort::Data8);
    port.setParity(QSerialPort::NoParity);
    port.setStopBits(QSerialPort::OneStop);

    CHECK( SettingsStringFormat::dpsStringFromPort(port) == "8-N-1" );
  }
}

TEST_CASE("baudeRateAndDpsStringFromSettings")
{
  SettingsRawData data;
  data.portName = "ttyS0";
  data.flowControl = QSerialPort::NoFlowControl;

  SECTION("9600-8-N-1")
  {
    data.baudRate = 9600;
    data.dataBits = QSerialPort::Data8;
    data.parity = QSerialPort::NoParity;
    data.stopBits = QSerialPort::OneStop;
    const Settings settings = SettingsBuilder::settingsFromRawData(data);

    CHECK( SettingsStringFormat::baudeRateAndDpsStringFromSettings(settings) == "9600-8-N-1" );
  }
}

TEST_CASE("baudeRateAndDpsStringFromPort")
{
  QSerialPort port;
  port.setPortName("ttyS0");

  SECTION("9600-8-N-1")
  {
    port.setBaudRate(9600);
    port.setDataBits(QSerialPort::Data8);
    port.setParity(QSerialPort::NoParity);
    port.setStopBits(QSerialPort::OneStop);

    CHECK( SettingsStringFormat::baudeRateAndDpsStringFromPort(port) == "9600-8-N-1" );
  }
}
