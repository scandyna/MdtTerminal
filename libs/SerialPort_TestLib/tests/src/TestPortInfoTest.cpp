// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/TestLib/TestPortInfo.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::TestLib;
using Mdt::SerialPort::PortInfo;


TEST_CASE("defaultConstruced")
{
  TestPortInfo pi;

  CHECK( pi.isNull() );
}

TEST_CASE("fromPortNameAndSystemLocation_PortInfo")
{
  const PortInfo pi = TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0");

  CHECK( pi.portName() == "ttyS0" );
  CHECK( pi.systemLocation() == "/dev/ttyS0" );
  CHECK( !pi.isNull() );
}

TEST_CASE("fromPortNameAndSystemLocation_TestPortInfo")
{
  const TestPortInfo pi = TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0");

  CHECK( !pi.isNull() );
  CHECK( pi.portName() == "ttyS0" );
  CHECK( pi.systemLocation() == "/dev/ttyS0" );
}

TEST_CASE("description")
{
  auto pi = TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0");

  pi.setDescription("Some description");

  CHECK( pi.description() == "Some description" );
}

TEST_CASE("manufacturer")
{
  auto pi = TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0");

  pi.setManufacturer("Some manufacturer");

  CHECK( pi.manufacturer() == "Some manufacturer" );
}

TEST_CASE("serialNumber")
{
  auto pi = TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0");

  pi.setSerialNumber("1385");

  CHECK( pi.serialNumber() == "1385" );
}

TEST_CASE("vendorIdentifier")
{
  auto pi = TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0");

  CHECK( !pi.hasVendorIdentifier() );

  pi.setVendorIdentifier(0x1234);

  CHECK( pi.hasVendorIdentifier() );
  CHECK( pi.vendorIdentifier() == 0x1234 );
  CHECK( pi.vendorIdentifierIfAvailable() == 0x1234 );
}

TEST_CASE("productIdentifier")
{
  auto pi = TestPortInfo::fromPortNameAndSystemLocation("ttyS0", "/dev/ttyS0");

  CHECK( !pi.hasProductIdentifier() );

  pi.setProductIdentifier(0x5678);

  CHECK( pi.hasProductIdentifier() );
  CHECK( pi.productIdentifier() == 0x5678 );
  CHECK( pi.productIdentifierIfAvailable() == 0x5678 );
}
