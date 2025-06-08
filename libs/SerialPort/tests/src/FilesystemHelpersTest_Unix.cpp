// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/FilesystemHelpers.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("qStringFromStdFilesystemPath")
{
  std::filesystem::path path = "relative/path/to/file.txt";

  CHECK( qStringFromStdFilesystemPath(path) == "relative/path/to/file.txt" );
}

TEST_CASE("stdFilesystemPathFromQString")
{
  CHECK( stdFilesystemPathFromQString("relative/path/to/file.txt") == std::filesystem::path("relative/path/to/file.txt") );
}
