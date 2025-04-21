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
#include "Mdt/SerialPort/BaudRateStringFormat.h"
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
  // Serial port specific attributes
  CHECK( editor.interfaceListModelForView()->rowCount() == 0 );
  CHECK( editor.interfaceListCurrentRow() == -1 );
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
    // Emulate QComboBox setting its current index to -1
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

TEST_CASE("PortSpecificAttributes")
{
  TestSettingsEditor editor;

  /*
   * The port name is not important for this test
   */
  Mdt::SerialPort::TestLib::TestPortInfo ttyS0;
  ttyS0.portName = "ttyS0";
  ttyS0.systemLocation = "/dev/ttyS0";

  SECTION("no serial port")
  {
    editor.fetchAvailablePorts();

    // Emulate QComboBox setting its current index to -1
    editor.setPortInfoListCurrentRowFromUi(-1);

    CHECK( editor.interfaceListModelForView()->rowCount() == 0 );
  }

  SECTION("common port supporting RS-232 only")
  {
    editor.addAvailablePort(ttyS0);
    editor.fetchAvailablePorts();

    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);

    CHECK( editor.interfaceListModelForView()->rowCount() == 1 );
  }

  SECTION("Port supporting multiple interfaces")
  {
    /*
     * Here we use a MOXA Uport 1250
     */
    ttyS0.vid = 0x110A;
    ttyS0.pid = 0x1250;
    editor.addAvailablePort(ttyS0);
    editor.fetchAvailablePorts();

    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);

    CHECK( editor.interfaceListModelForView()->rowCount() == 4 );
  }
}

TEST_CASE("CurrentInterface")
{
  TestSettingsEditor editor;

  /*
   * The port name is not important for this test
   */

  Mdt::SerialPort::TestLib::TestPortInfo commonPort;
  commonPort.portName = "ttyS0";
  commonPort.systemLocation = "/dev/ttyS0";

  Mdt::SerialPort::TestLib::TestPortInfo uport1250_1;
  uport1250_1.portName = "ttyS1";
  uport1250_1.systemLocation = "/dev/ttyS1";
  uport1250_1.vid = 0x110A;
  uport1250_1.pid = 0x1250;

  Mdt::SerialPort::TestLib::TestPortInfo uport1250_2;
  uport1250_2.portName = "ttyS2";
  uport1250_2.systemLocation = "/dev/ttyS2";
  uport1250_2.vid = 0x110A;
  uport1250_2.pid = 0x1250;

  SECTION("no serial port")
  {
    editor.fetchAvailablePorts();

    // Emulate QComboBox setting its current index to -1
    editor.setPortInfoListCurrentRowFromUi(-1);

    REQUIRE( editor.interfaceListModelForView()->rowCount() == 0 );
    CHECK( editor.interfaceListCurrentRow() == -1 );
  }

  SECTION("common port supporting RS-232 only")
  {
    editor.addAvailablePort(commonPort);
    editor.fetchAvailablePorts();

    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);
    editor.setInterfaceListCurrentRowFromUi(0);

    REQUIRE( editor.interfaceListModelForView()->rowCount() == 1 );
    CHECK( editor.interfaceListCurrentRow() == 0 );
  }

  SECTION("Port supporting multiple interfaces")
  {
    editor.addAvailablePort(uport1250_1);
    editor.fetchAvailablePorts();

    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);
    editor.setInterfaceListCurrentRowFromUi(0);

    REQUIRE( editor.interfaceListModelForView()->rowCount() == 4 );
    CHECK( editor.interfaceListCurrentRow() == 0 );

    editor.setInterfaceListCurrentRowFromUi(3);
    CHECK( editor.interfaceListCurrentRow() == 3 );
  }

  SECTION("change serial port")
  {
    editor.addAvailablePort(uport1250_1);
    editor.addAvailablePort(uport1250_2);
    editor.addAvailablePort(commonPort);
    editor.fetchAvailablePorts();
    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);
    editor.setInterfaceListCurrentRowFromUi(0);
    REQUIRE( editor.interfaceListModelForView()->rowCount() == 4 );
    REQUIRE( editor.interfaceListCurrentRow() == 0 );

    /*
     * Initially, this test was made after a bad feeling in the setting UI:
     * Having a MOXA UPort 1250, with 2 serial ports, each supporting 4 interfaces.
     * When selecting the RS-485 4 wire, then changing to the other port,
     * current index changed to RS-232.
     *
     * The actual and simple solution was to change InterfaceListTableModel,
     * so that it does not reset as long as the list stays the same size.
     *
     * If, in the future, some more sofisticated solution is required
     * (like the consept of current protocol),
     * this test should be adapted.
     */
    SECTION("select interface 3 - RS-485 4 wire")
    {
      editor.setInterfaceListCurrentRowFromUi(3);
      REQUIRE( editor.interfaceListCurrentRow() == 3 );

      SECTION("select second UPort 1250 - we should still have RS-485 4W selected")
      {
        editor.setPortInfoListCurrentRowFromUi(1);

        // Here, InterfaceListTableModel will not reset

        CHECK( editor.interfaceListCurrentRow() == 3 );
      }

      SECTION("select common port - RS-232 should be selected")
      {
        editor.setPortInfoListCurrentRowFromUi(2);

        // Emulate QComboBox setting its current index to the first element (after model reset)
        editor.setInterfaceListCurrentRowFromUi(0);

        CHECK( editor.interfaceListCurrentRow() == 0 );
      }
    }
  }
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
  data.sendByteByByteIsEnabled = true;
  data.sendByteByByteIntervalInMilliseconds = 50;

  const Settings settings = SettingsBuilder::settingsFromRawData(data);
  editor.setSettings(settings);

  CHECK( getModelData(*editor.baudRateListModelForView(), editor.baudRateListCurrentRow(), 0) == BaudRateStringFormat::toHumanFriendlyString(4800) );
  CHECK( getModelData(*editor.dataBitsListModelForView(), editor.dataBitsListCurrentRow(), 0).toInt() == 6 );
  const QString expectedParityStr = ParityStringFormat::parityToString( settings.parity() );
  CHECK( getModelData(*editor.parityListModelForView(), editor.parityListCurrentRow(), 0).toString() == expectedParityStr );
  const QString expectedFlowControlStr = FlowControlStringFormat::flowControlToString(QSerialPort::HardwareControl);
  CHECK( getModelData(*editor.flowControlListModelForView(), editor.flowControlListCurrentRow(), 0).toString() == expectedFlowControlStr );
  const QString expectedStopBitsStr = StopBitsStringFormat::stopBitsToString(QSerialPort::TwoStop);
  CHECK( getModelData(*editor.stopBitsListModelForView(), editor.stopBitsListCurrentRow(), 0).toString() == expectedStopBitsStr );
  CHECK( editor.sendByteByByteIsEnabled() );
  CHECK( editor.sendByteByByteIntervalInMilliseconds() == 50 );
}

TEST_CASE("setSettings_PortSpecificSettings")
{
  TestSettingsEditor editor;

  SettingsRawData settingsData;
  settingsData.baudRate = 4800;
  settingsData.dataBits = QSerialPort::Data6;
  settingsData.parity = QSerialPort::MarkParity;
  settingsData.flowControl = QSerialPort::HardwareControl;
  settingsData.stopBits = QSerialPort::TwoStop;

  Mdt::SerialPort::TestLib::TestPortInfo commonPort;
  commonPort.portName = "ttyS0";
  commonPort.systemLocation = "/dev/ttyS0";

  Mdt::SerialPort::TestLib::TestPortInfo uport1250_1;
  uport1250_1.portName = "ttyS1";
  uport1250_1.systemLocation = "/dev/ttyS1";
  uport1250_1.vid = 0x110A;
  uport1250_1.pid = 0x1250;

  /*
   * TODO What should be the behaviour ?
   * Admit we request an interface supporting RS-232.
   * We have no serial port.
   * Should the editor present an empty list with no selected interface ?
   * Later, the user plugs-in as USB-Serial device, then refreshes the list.
   * Then, the RS-232 interface becomes available.
   *
   * Current behaviour is to display an empty list,
   * and no current interface (index: -1).
   * Once a clear behaviour is known, this test should be adapted.
   */
  SECTION("no serial port")
  {
    editor.fetchAvailablePorts();
    // Emulate QComboBox setting its current index to -1
    editor.setPortInfoListCurrentRowFromUi(-1);
    editor.setInterfaceListCurrentRowFromUi(-1);

      settingsData.interfaceStandard = InterfaceStandard::RS_232;
      const Settings settings = SettingsBuilder::settingsFromRawData(settingsData);

      editor.setSettings(settings);

      CHECK( editor.interfaceListCurrentRow() == -1 );
  }

  SECTION("common port supporting RS-232 only")
  {
    editor.addAvailablePort(commonPort);
    editor.fetchAvailablePorts();
    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);
    editor.setInterfaceListCurrentRowFromUi(0);

    SECTION("RS-232")
    {
      settingsData.interfaceStandard = InterfaceStandard::RS_232;
      const Settings settings = SettingsBuilder::settingsFromRawData(settingsData);

      editor.setSettings(settings);

      CHECK( editor.interfaceListCurrentRow() == 0 );
    }

    /*
     * TODO What should be the behaviour ?
     *
     * Current behaviour is to display the RS-232 interface.
     * This means, we ignore the request settings (is this really a problem ?)
     * If the user then selects another serial port adapter,
     * that supports the requested interface standard,
     * the user will have to choose it.
     *
     * See also the remark in CurrentInterface test.
     *
     * Once a clear behaviour is known, this test should be adapted.
     */
    SECTION("Try RS-485 2W")
    {
      settingsData.interfaceStandard = InterfaceStandard::RS_485_2W;
      const Settings settings = SettingsBuilder::settingsFromRawData(settingsData);

      editor.setSettings(settings);

      CHECK( editor.interfaceListCurrentRow() == 0 );
    }
  }

  SECTION("Port supporting multiple interfaces")
  {
    editor.addAvailablePort(uport1250_1);
    editor.fetchAvailablePorts();
    // Emulate QComboBox setting its current index to the first element
    editor.setPortInfoListCurrentRowFromUi(0);
    editor.setInterfaceListCurrentRowFromUi(0);

    SECTION("RS-232")
    {
      settingsData.interfaceStandard = InterfaceStandard::RS_232;
      const Settings settings = SettingsBuilder::settingsFromRawData(settingsData);

      editor.setSettings(settings);

      CHECK( editor.interfaceListCurrentRow() == 0 );
    }

    SECTION("RS-485 2W")
    {
      settingsData.interfaceStandard = InterfaceStandard::RS_485_2W;
      const Settings settings = SettingsBuilder::settingsFromRawData(settingsData);

      editor.setSettings(settings);

      CHECK( editor.interfaceListCurrentRow() == 1 );
    }
  }
}
