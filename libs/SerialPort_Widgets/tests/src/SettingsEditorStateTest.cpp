// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SettingsEditorState.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using StateEnum = SettingsEditorState::StateEnum;


TEST_CASE("Incomplete")
{
  const auto state = SettingsEditorState::incomplete();

  CHECK( state.enumState() == StateEnum::Incomplete );
  CHECK( !state.canBuildSettings() );
  CHECK( state.canFetchAvailablePorts() );
}

TEST_CASE("Complete")
{
  const auto state = SettingsEditorState::complete();

  CHECK( state.enumState() == StateEnum::Complete );
  CHECK( state.canBuildSettings() );
  CHECK( state.canFetchAvailablePorts() );
}

TEST_CASE("FetchingSystemInfo")
{
  const auto state = SettingsEditorState::fetchingSystemInfo();

  CHECK( state.enumState() == StateEnum::FetchingSystemInfo );
  CHECK( !state.canBuildSettings() );
  CHECK( !state.canFetchAvailablePorts() );
}
