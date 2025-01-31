// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "TestSettingsEditor.h"
#include "Mdt/SerialPort/SettingsBuilder.h"
#include "Mdt/SerialPort/ParityStringFormat.h"
#include "Mdt/SerialPort/FlowControlStringFormat.h"
#include "Mdt/SerialPort/StopBitsStringFormat.h"
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
  TestSettingsEditor editor;

  CHECK( editor.portInfoListModelForView()->rowCount() == 0 );
  CHECK( editor.portInfoListCurrentRow() == -1 );
  CHECK( editor.baudRateListModelForView()->rowCount() == 0 );
  CHECK( editor.baudRateListCurrentRow() == -1 );
  CHECK( editor.dataBitsListModelForView()->rowCount() == 4 );
  CHECK( editor.dataBitsListCurrentRow() == 0 );
  CHECK( editor.parityListModelForView()->rowCount() == 5 );
  CHECK( editor.parityListCurrentRow() == 0 );
  CHECK( editor.flowControlListModelForView()->rowCount() == 3 );
  CHECK( editor.flowControlListCurrentRow() == 0 );
  CHECK( editor.stopBitsListModelForView()->rowCount() > 0 );
  CHECK( editor.stopBitsListCurrentRow() == 0 );
}

TEST_CASE("fetchAvailablePorts")
{
  TestSettingsEditor editor;

  editor.fetchAvailablePorts();

  Mdt::SerialPort::TestLib::TestPortInfo ttyS0;
  ttyS0.portName = "ttyS0";
  ttyS0.systemLocation = "/dev/ttyS0";

  Mdt::SerialPort::TestLib::TestPortInfo ttyUSB0;
  ttyUSB0.portName = "ttyUSB0";
  ttyUSB0.systemLocation = "/dev/ttyUSB0";

  SECTION("Initial state then system has 1 port")
  {
    editor.addAvailablePort(ttyS0);

    editor.fetchAvailablePorts();

    CHECK( editor.portInfoListModelForView()->rowCount() == 1 );
    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);
    CHECK( editor.portInfoListCurrentRow() == 0 );
    CHECK( editor.currentPortInfo().portName == "ttyS0" );
  }

  SECTION("We remove an USB serial port adapter then only 1 port remains")
  {
    editor.addAvailablePort(ttyUSB0);
    editor.addAvailablePort(ttyS0);
    editor.fetchAvailablePorts();
    REQUIRE( editor.portInfoListModelForView()->rowCount() == 2 );
    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);
    REQUIRE( editor.portInfoListCurrentRow() == 0 );
    REQUIRE( editor.currentPortInfo().portName == "ttyUSB0" );

    editor.removeAvailablePort(ttyUSB0);

    editor.fetchAvailablePorts();
    CHECK( editor.portInfoListModelForView()->rowCount() == 1 );
    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);
    CHECK( editor.portInfoListCurrentRow() == 0 );
    CHECK( editor.currentPortInfo().portName == "ttyS0" );
  }

  SECTION("We remove an USB serial port adapter then no port remains")
  {
    editor.addAvailablePort(ttyUSB0);
    editor.fetchAvailablePorts();
    REQUIRE( editor.portInfoListModelForView()->rowCount() == 1 );
    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);
    REQUIRE( editor.portInfoListCurrentRow() == 0 );
    REQUIRE( editor.currentPortInfo().portName == "ttyUSB0" );

    editor.removeAvailablePort(ttyUSB0);

    editor.fetchAvailablePorts();
    CHECK( editor.portInfoListModelForView()->rowCount() == 0 );
    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(-1);
    CHECK( editor.portInfoListCurrentRow() == -1 );
    REQUIRE( editor.currentPortInfo().portName.isEmpty() );
  }
}

TEST_CASE("fetchAvailablePortSettings")
{
  TestSettingsEditor editor;

  editor.fetchAvailablePortSettings();

  CHECK( editor.baudRateListModelForView()->rowCount() > 0 );
  // Emulate QComboBox setting its current index to the first element
  editor.setBaudRateListCurrentRowFromUi(0);
  CHECK( editor.baudRateListCurrentRow() == 0 );
}

TEST_CASE("setPortInfoListCurrentRowFromUi")
{
  TestSettingsEditor editor;

  Mdt::SerialPort::TestLib::TestPortInfo ttyS0;
  ttyS0.portName = "ttyS0";
  ttyS0.systemLocation = "/dev/ttyS0";

  SECTION("No port available")
  {
    editor.setPortInfoListCurrentRowFromUi(-1);
  }

  SECTION("Select first port")
  {
    editor.addAvailablePort(ttyS0);
    editor.fetchAvailablePorts();

    editor.setPortInfoListCurrentRowFromUi(0);

    CHECK( editor.currentPortInfo().portName == "ttyS0" );
  }

  // This will happen when we refresh port list and no more port is available
  SECTION("Select first port then none")
  {
    editor.addAvailablePort(ttyS0);
    editor.fetchAvailablePorts();

    editor.setPortInfoListCurrentRowFromUi(0);
    CHECK( editor.currentPortInfo().portName == "ttyS0" );

    editor.setPortInfoListCurrentRowFromUi(-1);

    CHECK( editor.currentPortInfo().portName.isEmpty() );
  }
}

TEST_CASE("setSettings")
{
  TestSettingsEditor editor;

  editor.fetchAvailablePortSettings();

  SettingsRawData data;
  data.baudRate = 4800;
  data.dataBits = QSerialPort::Data6;
  data.parity = QSerialPort::MarkParity;
  data.flowControl = QSerialPort::HardwareControl;
  data.stopBits = QSerialPort::TwoStop;

  const Settings settings = SettingsBuilder::settingsFromRawData(data);
  editor.setSettings(settings);

  CHECK( getModelData(*editor.baudRateListModelForView(), editor.baudRateListCurrentRow(), 0).toInt() == 4800 );
  CHECK( getModelData(*editor.dataBitsListModelForView(), editor.dataBitsListCurrentRow(), 0).toInt() == 6 );
  const QString expectedParityStr = ParityStringFormat::parityToString( settings.parity() );
  CHECK( getModelData(*editor.parityListModelForView(), editor.parityListCurrentRow(), 0).toString() == expectedParityStr );
  const QString expectedFlowControlStr = FlowControlStringFormat::flowControlToString(QSerialPort::HardwareControl);
  CHECK( getModelData(*editor.flowControlListModelForView(), editor.flowControlListCurrentRow(), 0).toString() == expectedFlowControlStr );
  const QString expectedStopBitsStr = StopBitsStringFormat::stopBitsToString(QSerialPort::TwoStop);
  CHECK( getModelData(*editor.stopBitsListModelForView(), editor.stopBitsListCurrentRow(), 0).toString() == expectedStopBitsStr );
}
