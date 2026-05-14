// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PortInfo.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include <QSerialPortInfo>

using namespace Mdt::SerialPort;


TEST_CASE("fromQSerialPortInfo")
{
  const auto qPortInfoList = QSerialPortInfo::availablePorts();
  REQUIRE( qPortInfoList.size() > 0 );
  const QSerialPortInfo qPortInfo = qPortInfoList.at(0);
  REQUIRE( !qPortInfo.portName().isEmpty() );
  REQUIRE( !qPortInfo.systemLocation().isEmpty() );

  const PortInfo pi = PortInfo::fromQSerialPortInfo(qPortInfo);

  CHECK( pi.portName() == qPortInfo.portName() );
  CHECK( pi.systemLocation() == qPortInfo.systemLocation() );
  CHECK( pi.description() == qPortInfo.description() );
  CHECK( pi.manufacturer() == qPortInfo.manufacturer() );
  CHECK( pi.serialNumber() == qPortInfo.serialNumber() );
  if( qPortInfo.hasVendorIdentifier() ){
    CHECK( pi.hasVendorIdentifier() );
    CHECK( pi.vendorIdentifier() == qPortInfo.vendorIdentifier() );
  }
  if( qPortInfo.hasProductIdentifier() ){
    CHECK( pi.hasProductIdentifier() );
    CHECK( pi.productIdentifier() == qPortInfo.productIdentifier() );
  }
}
