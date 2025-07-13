// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Linux/UdevContext.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"
#include <memory>

using namespace Mdt::SerialPort::Linux;


TEST_CASE("BasicTest")
{
  const auto context = std::make_shared<UdevContext>();

  CHECK( context->nativePointer() != nullptr );
}
