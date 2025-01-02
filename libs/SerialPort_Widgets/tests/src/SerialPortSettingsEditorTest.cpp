// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SettingsEditor.h"
#include "Mdt/SerialPort/SettingsBuilder.h"
#include <Mdt/ItemModel/Helpers.h>
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using Mdt::ItemModel::getModelData;

/*
 * NOTE: tests are made with the assumtion that QComboBox are used
 * to list the available enumerated properties.
 * This is important, because QComboBox will emit currentIndexChanged()
 * after a model reset, with the index to the first enabled item.
 * For more details, see QComboBoxPrivate::_q_modelReset()
 * and QComboBoxPrivate::trySetValidIndex()
 */

TEST_CASE("default_constructed")
{
  SettingsEditor editor;

  CHECK( editor.baudRateListModelForView()->rowCount() == 0 );
  CHECK( editor.baudRateListCurrentRow() == -1 );
}

TEST_CASE("fetchAvailablePortSettings")
{
  SettingsEditor editor;

  editor.fetchAvailablePortSettings();

  CHECK( editor.baudRateListModelForView()->rowCount() > 0 );
  // Emulate QComboBox setting its current index to the first element
  editor.setBaudRateListCurrentRowFromUi(0);
  CHECK( editor.baudRateListCurrentRow() == 0 );
}

TEST_CASE("setSettings")
{
  SettingsEditor editor;

  editor.fetchAvailablePortSettings();

  SettingsRawData data;
  data.baudRate = 4800;

  const Settings settings = SettingsBuilder::settingsFromRawData(data);
  editor.setSettings(settings);

  CHECK( getModelData(*editor.baudRateListModelForView(), editor.baudRateListCurrentRow(), 0).toInt() == 4800 );
}
