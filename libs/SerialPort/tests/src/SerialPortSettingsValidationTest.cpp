// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SettingsValidation.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("validateSettings")
{
  SettingsRawData data;

  SECTION("default constructed settings raw data")
  {
    REQUIRE_THROWS_AS( SettingsValidation::validateSettings(data), SettingsValidationError );
  }

  SECTION("Valid settings")
  {
    data.baudRate = 4800;
    data.dataBits = QSerialPort::Data7;
    data.parity = QSerialPort::MarkParity;

    SettingsValidation::validateSettings(data);
  }
}

TEST_CASE("validateBaudRate")
{
  SECTION("Invalid rate")
  {
    REQUIRE_THROWS_AS( SettingsValidation::validateBaudRate(-1), SettingsValidationError );
  }

  SECTION("valid rate")
  {
    SettingsValidation::validateBaudRate(4800);
  }
}

TEST_CASE("validateDataBits")
{
  SECTION("Invalid data bits")
  {
    REQUIRE_THROWS_AS( SettingsValidation::validateDataBits(QSerialPort::UnknownDataBits), SettingsValidationError );
  }

  SECTION("5 data bits is ok")
  {
    SettingsValidation::validateDataBits(QSerialPort::Data5);
  }
}

TEST_CASE("validateParity")
{
  SECTION("Invalid parity")
  {
    REQUIRE_THROWS_AS( SettingsValidation::validateParity(QSerialPort::UnknownParity), SettingsValidationError );
  }

  SECTION("Even parity is ok")
  {
    SettingsValidation::validateParity(QSerialPort::EvenParity);
  }
}
