// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/TestLib/TestPortInfoListTableModel.h"
#include "Mdt/ItemModel/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"


// using namespace Mdt::SerialPort;
using namespace Mdt::SerialPort::TestLib;
using Mdt::ItemModel::getModelData;

constexpr int portNameColumn = TestPortInfoListTableModel::portNameColumnIndex();


TEST_CASE("defaultConstructed")
{
  TestPortInfoListTableModel model;

  REQUIRE( model.columnCount() == 7 );
  REQUIRE( model.rowCount() == 0 );
}

TEST_CASE("removeAvailablePort")
{
  TestPortInfoListTableModel model;

  TestPortInfo ttyUSB0;
  ttyUSB0.portName = "ttyUSB0";
  ttyUSB0.systemLocation = "/dev/ttyUSB0";

  TestPortInfo ttyS0;
  ttyS0.portName = "ttyS0";
  ttyS0.systemLocation = "/dev/ttyS0";

  model.addAvailablePort(ttyUSB0);
  model.addAvailablePort(ttyS0);

  model.fetchAvailablePorts();
  REQUIRE( model.rowCount() == 2 );
  REQUIRE( getModelData(model, 0, portNameColumn).toString() == "ttyUSB0" );
  REQUIRE( getModelData(model, 1, portNameColumn).toString() == "ttyS0" );

  SECTION("remove ttyUSB0")
  {
    model.removeAvailablePort(ttyUSB0);
    model.fetchAvailablePorts();

    CHECK( model.rowCount() == 1 );
    CHECK( getModelData(model, 0, portNameColumn).toString() == "ttyS0" );
  }

  SECTION("remove ttyS0")
  {
    model.removeAvailablePort(ttyS0);
    model.fetchAvailablePorts();

    CHECK( model.rowCount() == 1 );
    CHECK( getModelData(model, 0, portNameColumn).toString() == "ttyUSB0" );
  }

  SECTION("remove both")
  {
    model.removeAvailablePort(ttyS0);
    model.removeAvailablePort(ttyUSB0);
    model.fetchAvailablePorts();

    CHECK( model.rowCount() == 0 );
  }
}
