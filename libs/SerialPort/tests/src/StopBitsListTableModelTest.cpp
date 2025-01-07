// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/StopBitsListTableModel.h"
#include "Mdt/SerialPort/StopBitsStringFormat.h"
#include "Mdt/SerialPort/Settings.h"
#include "Mdt/ItemModel/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::ItemModel::getModelData;

// constexpr
// int expectedRowCount() noexcept
// {
// }

TEST_CASE("defaultConstructed")
{
  StopBitsListTableModel model;

  REQUIRE( model.columnCount() == 1 );

  if( oneAndHalfStopBitsIsSupported() ){
    REQUIRE( model.rowCount() == 3 );
  }else{
    REQUIRE( model.rowCount() == 2 );
  }

  CHECK( getModelData(model, 0, 0).toString() == StopBitsStringFormat::stopBitsToString(QSerialPort::OneStop) );
  if( oneAndHalfStopBitsIsSupported() ){
    CHECK( getModelData(model, 1, 0).toString() == StopBitsStringFormat::stopBitsToString(QSerialPort::OneAndHalfStop) );
    CHECK( getModelData(model, 2, 0).toString() == StopBitsStringFormat::stopBitsToString(QSerialPort::TwoStop) );
  }else{
    CHECK( getModelData(model, 1, 0).toString() == StopBitsStringFormat::stopBitsToString(QSerialPort::TwoStop) );
  }
}

TEST_CASE("stopBitsAtRow")
{
  StopBitsListTableModel model;

  CHECK( model.stopBitsAtRow(0) == QSerialPort::OneStop );
  if( oneAndHalfStopBitsIsSupported() ){
    CHECK( model.stopBitsAtRow(1) == QSerialPort::OneAndHalfStop );
    CHECK( model.stopBitsAtRow(2) == QSerialPort::TwoStop );
  }else{
    CHECK( model.stopBitsAtRow(1) == QSerialPort::TwoStop );
  }
}

TEST_CASE("findRowOfStopBits")
{
  StopBitsListTableModel model;

  CHECK( model.findRowOfStopBits(QSerialPort::OneStop) == 0 );
  if( oneAndHalfStopBitsIsSupported() ){
    CHECK( model.findRowOfStopBits(QSerialPort::OneAndHalfStop) == 1 );
    CHECK( model.findRowOfStopBits(QSerialPort::TwoStop) == 2 );
  }else{
    CHECK( model.findRowOfStopBits(QSerialPort::TwoStop) == 1 );
  }
}
