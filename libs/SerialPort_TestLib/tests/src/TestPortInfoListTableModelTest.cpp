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


TEST_CASE("defaultConstructed")
{
  TestPortInfoListTableModel model;

  REQUIRE( model.columnCount() == 7 );
  REQUIRE( model.rowCount() == 0 );
}
