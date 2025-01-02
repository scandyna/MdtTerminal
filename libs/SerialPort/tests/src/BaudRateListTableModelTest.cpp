// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/BaudRateListTableModel.h"
#include "Mdt/ItemModel/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::ItemModel::getModelData;


TEST_CASE("defaultConstructed")
{
  BaudRateListTableModel model;

  REQUIRE( model.rowCount() == 0 );
  REQUIRE( model.columnCount() == 1 );
}

TEST_CASE("fetchStandardBaudRates")
{
  BaudRateListTableModel model;

  model.fetchStandardBaudRates();

  REQUIRE( model.rowCount() > 0 );
  REQUIRE( getModelData(model, 0, 0).toInt() > 0 );
}

TEST_CASE("findRowOfBaudRate")
{
  BaudRateListTableModel model;

  SECTION("empty list")
  {
    REQUIRE( model.findRowOfBaudRate(4800) == -1 );
  }

  SECTION("list contains requested baud rate")
  {
    model.setBaudRateList({1200,9600});

    REQUIRE( model.findRowOfBaudRate(4800) == -1 );
  }

  SECTION("list does not contain requested baud rate")
  {
    model.setBaudRateList({1200,4800});

    REQUIRE( model.findRowOfBaudRate(4800) == 1 );
  }
}
