// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PinoutSignals.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("defaultConstructed")
{
  PinoutSignals ps;

  CHECK( !ps.receiveDataIsOn() );
  CHECK( !ps.transmitDataIsOn() );
  CHECK( !ps.dataTerminalReadyIsOn() );
  CHECK( !ps.requestToSendIsOn() );
}

TEST_CASE("set_RX")
{
  PinoutSignals ps;

  ps.setReceiveDataOn(true);
  CHECK( ps.receiveDataIsOn() );

  ps.setReceiveDataOn(false);
  CHECK( !ps.receiveDataIsOn() );
}

TEST_CASE("set_TX")
{
  PinoutSignals ps;

  ps.setTransmitDataOn(true);
  CHECK( ps.transmitDataIsOn() );

  ps.setTransmitDataOn(false);
  CHECK( !ps.transmitDataIsOn() );
}

TEST_CASE("setSignals")
{
  PinoutSignals ps;
  QSerialPort::PinoutSignals sps = QSerialPort::NoSignal;

  SECTION("DTR is ON")
  {
    sps = QSerialPort::DataTerminalReadySignal;

    ps.setSignals(sps);
    CHECK( ps.dataTerminalReadyIsOn() );
  }

  SECTION("RTS is ON")
  {
    sps = QSerialPort::RequestToSendSignal;

    ps.setSignals(sps);
    CHECK( ps.requestToSendIsOn() );
  }

  SECTION("DCD is ON")
  {
    sps = QSerialPort::DataCarrierDetectSignal;

    ps.setSignals(sps);
    CHECK( ps.dataCarrierDetectIsOn() );
  }
}

TEST_CASE("setDataTerminalReadyOn")
{
  PinoutSignals ps;
  QSerialPort::PinoutSignals sps = QSerialPort::DataCarrierDetectSignal;
  ps.setSignals(sps);
  REQUIRE( !ps.dataTerminalReadyIsOn() );
  REQUIRE( ps.dataCarrierDetectIsOn() );

  ps.setDataTerminalReadyOn(true);
  CHECK( ps.dataTerminalReadyIsOn() );
  CHECK( ps.dataCarrierDetectIsOn() );

  ps.setDataTerminalReadyOn(false);
  CHECK( !ps.dataTerminalReadyIsOn() );
  CHECK( ps.dataCarrierDetectIsOn() );
}

TEST_CASE("setRequestToSendOn")
{
  PinoutSignals ps;
  QSerialPort::PinoutSignals sps = QSerialPort::DataCarrierDetectSignal;
  ps.setSignals(sps);
  REQUIRE( !ps.requestToSendIsOn() );
  REQUIRE( ps.dataCarrierDetectIsOn() );

  ps.setRequestToSendOn(true);
  CHECK( ps.requestToSendIsOn() );
  CHECK( ps.dataCarrierDetectIsOn() );

  ps.setRequestToSendOn(false);
  CHECK( !ps.requestToSendIsOn() );
  CHECK( ps.dataCarrierDetectIsOn() );
}

TEST_CASE("clear")
{
  PinoutSignals ps;

  ps.setReceiveDataOn(true);
  ps.setTransmitDataOn(true);
  ps.setDataTerminalReadyOn(true);
  ps.setRequestToSendOn(true);

  ps.clear();

  CHECK( !ps.receiveDataIsOn() );
  CHECK( !ps.transmitDataIsOn() );
  CHECK( !ps.dataTerminalReadyIsOn() );
  CHECK( !ps.requestToSendIsOn() );
}

TEST_CASE("comparison")
{
  PinoutSignals a;
  PinoutSignals b;
  QSerialPort::PinoutSignals sps = QSerialPort::NoSignal;

  SECTION("default constructed a and b are equal")
  {
    CHECK( a == b );
    CHECK( !(a != b) );
  }

  SECTION("RX differs")
  {
    a.setReceiveDataOn(true);

    CHECK( a != b );
    CHECK( !(a == b) );
  }

  SECTION("TX differs")
  {
    a.setTransmitDataOn(true);

    CHECK( a != b );
  }

  SECTION("DTR differs")
  {
    sps = QSerialPort::DataTerminalReadySignal;
    a.setSignals(sps);

    CHECK( a != b );
  }

  SECTION("RTS differs")
  {
    sps = QSerialPort::RequestToSendSignal;
    a.setSignals(sps);

    CHECK( a != b );
  }
}
