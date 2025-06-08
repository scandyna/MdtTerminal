// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Unix/FileStatus.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::Unix;


TEST_CASE("fromStatStruct")
{
  struct stat st;
  st.st_dev = 1234;

  const auto fileStatus = FileStatus::fromStatStruct(st);

  CHECK( fileStatus.deviceId() == 1234 );
}

TEST_CASE("blockDevice")
{
  struct stat st;
  st.st_rdev = 4321;
  st.st_mode = 0060000; // Octal notation

  const auto fileStatus = FileStatus::fromStatStruct(st);

  CHECK( fileStatus.representedDeviceId() == 4321 );
  CHECK( fileStatus.isBlockDevice() );
  CHECK( !fileStatus.isCharacterDevice() );
}

TEST_CASE("characterDevice")
{
  struct stat st;
  st.st_rdev = 4321;
  st.st_mode = 0020000; // Octal notation

  const auto fileStatus = FileStatus::fromStatStruct(st);

  CHECK( fileStatus.representedDeviceId() == 4321 );
  CHECK( !fileStatus.isBlockDevice() );
  CHECK( fileStatus.isCharacterDevice() );
}
