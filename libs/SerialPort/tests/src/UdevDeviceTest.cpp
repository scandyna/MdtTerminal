// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Linux/UdevDevice.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::Linux;
using Mdt::SerialPort::Unix::FileStatusFileType;


TEST_CASE("deviceTypeCharFromFileType")
{
  CHECK( UdevDevice::deviceTypeCharFromFileType(FileStatusFileType::BlockDevice) == 'b' );
  CHECK( UdevDevice::deviceTypeCharFromFileType(FileStatusFileType::CharacterDevice) == 'c' );
  CHECK( UdevDevice::deviceTypeCharFromFileType(FileStatusFileType::RegularFile) == '\0' );
}
