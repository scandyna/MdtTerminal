// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SettingsEditor.h"
#include <Mdt/ItemModel/Helpers.h>
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::ItemModel::getModelData;


TEST_CASE("default_constructed")
{
  SettingsEditor editor;

  CHECK( editor.portInfoListModelForView()->rowCount() == 0 );
  CHECK( editor.portInfoListCurrentRow() == -1 );
}

TEST_CASE("fetchAvailablePorts")
{
  SettingsEditor editor;

  editor.fetchAvailablePorts();

  CHECK( editor.portInfoListModelForView()->rowCount() > 0 );
}

TEST_CASE("setPortInfoListCurrentRowFromUi")
{
  SettingsEditor editor;

  SECTION("No port available")
  {
    editor.setPortInfoListCurrentRowFromUi(-1);
  }

  SECTION("Select first port")
  {
    editor.fetchAvailablePorts();

    editor.setPortInfoListCurrentRowFromUi(0);
  }

  // This will happen when we refresh port list and no more port is available
  SECTION("Select first port then none")
  {
    editor.fetchAvailablePorts();

    editor.setPortInfoListCurrentRowFromUi(0);

    editor.setPortInfoListCurrentRowFromUi(-1);
  }
}
