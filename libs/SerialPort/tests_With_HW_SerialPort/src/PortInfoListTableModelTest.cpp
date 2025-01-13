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
#include "Mdt/ItemModel/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::ItemModel::getModelData;

constexpr int portNameColumn = PortInfoListTableModel::portNameColumnIndex();
constexpr int systemLocationColumn = PortInfoListTableModel::systemLocationColumnIndex();


TEST_CASE("defaultConstructed")
{
  PortInfoListTableModel model;

  REQUIRE( model.columnCount() == 7 );
  REQUIRE( model.rowCount() == 0 );
}

TEST_CASE("getData")
{
  PortInfoListTableModel model;

  model.fetchAvailablePorts();
  REQUIRE( model.rowCount() > 0 );

  CHECK( !getModelData(model, 0, portNameColumn).toString().isEmpty() );
  CHECK( !getModelData(model, 0, systemLocationColumn).toString().isEmpty() );
}

TEST_CASE("portInfoAtRow")
{
  PortInfoListTableModel model;

  model.fetchAvailablePorts();
  REQUIRE( model.rowCount() > 0 );

  CHECK( !model.portInfoAtRow(0).portName().isEmpty() );
}
