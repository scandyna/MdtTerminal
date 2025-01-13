// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PortInfoListTableModel.h"
#include "Mdt/SerialPort/PortInfoStringFormat.h"
#include "Mdt/ItemModel/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include "Mdt/SerialPort/TestLib/TestPortInfoListTableModel.h"

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

TEST_CASE("getData")
{
  TestPortInfoListTableModel model;

  TestPortInfo port;
  port.portName = "ttyS0";
  port.systemLocation = "/dev/ttyS0";
  port.description = "Some description";
  port.manufacturer = "Some manufacturer";
  port.serialNumber = "ABCDE";
  port.vid = 0x1234;
  port.pid = 0x5678;
  model.addAvailablePort(port);

  model.fetchAvailablePorts();
  REQUIRE( model.rowCount() == 1 );

  CHECK( getModelData(model, 0, portNameColumn).toString() == "ttyS0" );
  CHECK( getModelData(model, 0, systemLocationColumn).toString() == "/dev/ttyS0" );
  CHECK( getModelData(model, 0, descriptionColumn).toString() == "Some description" );
  CHECK( getModelData(model, 0, manufacturerColumn).toString() == "Some manufacturer" );
  CHECK( getModelData(model, 0, serialNumberColumn).toString() == "ABCDE" );
  CHECK( getModelData(model, 0, vendorIdentifierColumn).toString() == PortInfoStringFormat::vendorIdentifierToString(0x1234) );
  CHECK( getModelData(model, 0, productIdentifierColumn).toString() == PortInfoStringFormat::productIdentifierToString(0x5678) );
}
