// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/DataBitsListTableModel.h"
#include "Mdt/ItemModel/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::ItemModel::getModelData;


TEST_CASE("defaultConstructed")
{
  DataBitsListTableModel model;

  REQUIRE( model.columnCount() == 1 );
  REQUIRE( model.rowCount() == 4 );
  CHECK( getModelData(model, 0, 0) == QVariant(5) );
  CHECK( getModelData(model, 1, 0) == QVariant(6) );
  CHECK( getModelData(model, 2, 0) == QVariant(7) );
  CHECK( getModelData(model, 3, 0) == QVariant(8) );
}

TEST_CASE("findRowOfDataBits")
{
  DataBitsListTableModel model;

  CHECK( model.findRowOfDataBits(QSerialPort::Data5) == 0 );
  CHECK( model.findRowOfDataBits(QSerialPort::Data6) == 1 );
  CHECK( model.findRowOfDataBits(QSerialPort::Data7) == 2 );
  CHECK( model.findRowOfDataBits(QSerialPort::Data8) == 3 );
}

TEST_CASE("dataBitsAtRow")
{
  DataBitsListTableModel model;

  CHECK( model.dataBitsAtRow(0) == QSerialPort::Data5 );
  CHECK( model.dataBitsAtRow(1) == QSerialPort::Data6 );
  CHECK( model.dataBitsAtRow(2) == QSerialPort::Data7 );
  CHECK( model.dataBitsAtRow(3) == QSerialPort::Data8 );
}
