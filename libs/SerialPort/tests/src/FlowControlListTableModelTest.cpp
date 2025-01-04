// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/FlowControlListTableModel.h"
#include "Mdt/SerialPort/FlowControlStringFormat.h"
#include "Mdt/ItemModel/Helpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::ItemModel::getModelData;


TEST_CASE("defaultConstructed")
{
  FlowControlListTableModel model;

  REQUIRE( model.columnCount() == 1 );
  REQUIRE( model.rowCount() == 3 );
  CHECK( getModelData(model, 0, 0).toString() == FlowControlStringFormat::flowControlToString(QSerialPort::NoFlowControl) );
  CHECK( getModelData(model, 1, 0).toString() == FlowControlStringFormat::flowControlToString(QSerialPort::HardwareControl) );
  CHECK( getModelData(model, 2, 0).toString() == FlowControlStringFormat::flowControlToString(QSerialPort::SoftwareControl) );
}

TEST_CASE("flowControlAtRow")
{
  FlowControlListTableModel model;

  CHECK( model.flowControlAtRow(0) == QSerialPort::NoFlowControl );
  CHECK( model.flowControlAtRow(1) == QSerialPort::HardwareControl );
  CHECK( model.flowControlAtRow(2) == QSerialPort::SoftwareControl );
}

TEST_CASE("findRowOfFlowControl")
{
  FlowControlListTableModel model;

  CHECK( model.findRowOfFlowControl(QSerialPort::NoFlowControl) == 0 );
  CHECK( model.findRowOfFlowControl(QSerialPort::HardwareControl) == 1 );
  CHECK( model.findRowOfFlowControl(QSerialPort::SoftwareControl) == 2 );
}
