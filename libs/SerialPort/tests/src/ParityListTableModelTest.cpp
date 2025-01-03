// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/ParityListTableModel.h"
#include "Mdt/ItemModel/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::ItemModel::getModelData;


TEST_CASE("defaultConstructed")
{
  ParityListTableModel model;

  REQUIRE( model.columnCount() == 1 );
  REQUIRE( model.rowCount() == 5 );
  // Strings are translated - just check that a non empty result is returned
  CHECK( !getModelData(model, 0, 0).toString().isEmpty() );
  CHECK( !getModelData(model, 1, 0).toString().isEmpty() );
  CHECK( !getModelData(model, 2, 0).toString().isEmpty() );
  CHECK( !getModelData(model, 3, 0).toString().isEmpty() );
  CHECK( !getModelData(model, 4, 0).toString().isEmpty() );
}

TEST_CASE("findRowOfParity")
{
  ParityListTableModel model;

  CHECK( model.findRowOfParity(QSerialPort::NoParity) == 0 );
  CHECK( model.findRowOfParity(QSerialPort::EvenParity) == 1 );
  CHECK( model.findRowOfParity(QSerialPort::OddParity) == 2 );
  CHECK( model.findRowOfParity(QSerialPort::SpaceParity) == 3 );
  CHECK( model.findRowOfParity(QSerialPort::MarkParity) == 4 );
}

TEST_CASE("parityAtRow")
{
  ParityListTableModel model;

  CHECK( model.parityAtRow(0) == QSerialPort::NoParity );
  CHECK( model.parityAtRow(1) == QSerialPort::EvenParity );
  CHECK( model.parityAtRow(2) == QSerialPort::OddParity );
  CHECK( model.parityAtRow(3) == QSerialPort::SpaceParity );
  CHECK( model.parityAtRow(4) == QSerialPort::MarkParity );
}
