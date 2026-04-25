// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/TestLib/TestPortInfoListTableModel.h"
#include "Mdt/SerialPort/PortInfoStringFormat.h"
#include "Mdt/ItemModel/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"


using namespace Mdt::SerialPort;
using namespace Mdt::SerialPort::TestLib;
using Mdt::ItemModel::getModelData;

constexpr int portNameColumn = TestPortInfoListTableModel::portNameColumnIndex();
constexpr int systemLocationColumn = TestPortInfoListTableModel::systemLocationColumnIndex();
constexpr int descriptionColumn = TestPortInfoListTableModel::descriptionColumnIndex();
constexpr int manufacturerColumn = TestPortInfoListTableModel::manufacturerColumnIndex();
constexpr int serialNumberColumn = TestPortInfoListTableModel::serialNumberColumnIndex();
constexpr int vendorIdentifierColumn = TestPortInfoListTableModel::vendorIdentifierColumnIndex();
constexpr int productIdentifierColumn = TestPortInfoListTableModel::productIdentifierColumnIndex();


TEST_CASE("defaultConstructed")
{
  TestPortInfoListTableModel model;

  REQUIRE( model.columnCount() == 7 );
  REQUIRE( model.rowCount() == 0 );
}

TEST_CASE("GetAttributes")
{
  TestPortInfoListTableModel model;

  TestPortInfo ttyUSB0;
  ttyUSB0.setPortName("ttyUSB0");
  ttyUSB0.systemLocation = "/dev/ttyUSB0";
  ttyUSB0.description = "Some description";
  ttyUSB0.manufacturer = "Some manufacturer";
  ttyUSB0.serialNumber = "28546";
  ttyUSB0.vid = 0x1234;
  ttyUSB0.pid = 0x5678;

  model.addAvailablePort(ttyUSB0);

  model.fetchAvailablePorts(PortListSorting::None);
  REQUIRE( model.rowCount() == 1 );

  CHECK( getModelData(model, 0, portNameColumn).toString() == "ttyUSB0" );
  CHECK( getModelData(model, 0, systemLocationColumn).toString() == "/dev/ttyUSB0" );
  CHECK( getModelData(model, 0, descriptionColumn).toString() == "Some description" );
  CHECK( getModelData(model, 0, manufacturerColumn).toString() == "Some manufacturer" );
  CHECK( getModelData(model, 0, serialNumberColumn).toString() == "28546" );
  CHECK( getModelData(model, 0, vendorIdentifierColumn).toString() == PortInfoStringFormat::vendorIdentifierToString(0x1234) );
  CHECK( getModelData(model, 0, productIdentifierColumn).toString() == PortInfoStringFormat::productIdentifierToString(0x5678) );
  CHECK( model.vendorIdentifierAtRow(0) == 0x1234 );
  CHECK( model.productIdentifierAtRow(0) == 0x5678 );
}

TEST_CASE("removeAvailablePort")
{
  TestPortInfoListTableModel model;

  TestPortInfo ttyUSB0;
  ttyUSB0.setPortName("ttyUSB0");
  ttyUSB0.systemLocation = "/dev/ttyUSB0";

  TestPortInfo ttyS0;
  ttyS0.setPortName("ttyS0");
  ttyS0.systemLocation = "/dev/ttyS0";

  model.addAvailablePort(ttyUSB0);
  model.addAvailablePort(ttyS0);

  model.fetchAvailablePorts(PortListSorting::None);
  REQUIRE( model.rowCount() == 2 );
  REQUIRE( getModelData(model, 0, portNameColumn).toString() == "ttyUSB0" );
  REQUIRE( getModelData(model, 1, portNameColumn).toString() == "ttyS0" );

  SECTION("remove ttyUSB0")
  {
    model.removeAvailablePort(ttyUSB0);
    model.fetchAvailablePorts(PortListSorting::None);

    CHECK( model.rowCount() == 1 );
    CHECK( getModelData(model, 0, portNameColumn).toString() == "ttyS0" );
  }

  SECTION("remove ttyS0")
  {
    model.removeAvailablePort(ttyS0);
    model.fetchAvailablePorts(PortListSorting::None);

    CHECK( model.rowCount() == 1 );
    CHECK( getModelData(model, 0, portNameColumn).toString() == "ttyUSB0" );
  }

  SECTION("remove both")
  {
    model.removeAvailablePort(ttyS0);
    model.removeAvailablePort(ttyUSB0);
    model.fetchAvailablePorts(PortListSorting::None);

    CHECK( model.rowCount() == 0 );
  }
}
