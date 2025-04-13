// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/InterfaceListTableModel.h"
#include "Mdt/SerialPort/InterfaceStringFormat.h"
#include "Mdt/ItemModel/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::ItemModel::getModelData;

constexpr int nameColumn = InterfaceListTableModel::nameColumn();
constexpr int parameterValueColumn = InterfaceListTableModel::parameterValueColumn();


TEST_CASE("DefaultList")
{
  InterfaceListTableModel model;

  CHECK( model.columnCount() == 2 );
  CHECK( model.rowCount() == 0 );
}

TEST_CASE("setVendorIdentifierAndProductIdentifier")
{
  InterfaceListTableModel model;

  SECTION("No VID - No PID")
  {
    model.setVendorIdentifierAndProductIdentifier({}, {});

    CHECK( model.rowCount() == 1 );
  }

  // PID: UPort 1250
  SECTION("No VID - PID 0x1250")
  {
    model.setVendorIdentifierAndProductIdentifier({}, 0x1250);

    CHECK( model.rowCount() == 1 );
  }

  // VID: MOXA
  SECTION("VID 0x110A - No PID")
  {
    model.setVendorIdentifierAndProductIdentifier(0x110A, {});

    CHECK( model.rowCount() == 1 );
  }

  SECTION("VID 0 - PID 0")
  {
    model.setVendorIdentifierAndProductIdentifier(0, 0);

    CHECK( model.rowCount() == 1 );
  }

  SECTION("MOXA UPort 1250 with 4 interfaces")
  {
    model.setVendorIdentifierAndProductIdentifier(0x110A, 0x1250);

    CHECK( model.rowCount() == 4 );
  }
}

TEST_CASE("getData")
{
  InterfaceListTableModel model;
  model.setVendorIdentifierAndProductIdentifier(0, 0);
  REQUIRE( model.rowCount() == 1 );

  CHECK( getModelData(model, 0, nameColumn) == InterfaceStringFormat::rs232Name() );
  CHECK( getModelData(model, 0, parameterValueColumn).isNull() );
}

TEST_CASE("clear")
{
  InterfaceListTableModel model;
  model.setVendorIdentifierAndProductIdentifier(0, 0);
  REQUIRE( model.columnCount() == 2 );
  REQUIRE( model.rowCount() == 1 );

  model.clear();

  CHECK( model.columnCount() == 2 );
  CHECK( model.rowCount() == 0 );
}
