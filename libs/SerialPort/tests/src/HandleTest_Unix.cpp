// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Handle.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("nativeHandleIsNull")
{
  CHECK( Handle::nativeHandleIsNull(-1) );
  CHECK( !Handle::nativeHandleIsNull(1) );
}

TEST_CASE("CreateAndUse")
{
  SECTION("Null handle")
  {
    const auto handle = Handle::fromNativeHandle(-1);

    CHECK( handle.isNull() );
  }

  SECTION("handle representing an open port")
  {
    const auto handle = Handle::fromNativeHandle(1);

    CHECK( !handle.isNull() );
    CHECK( handle.nativeHandle() == 1 );
  }
}
