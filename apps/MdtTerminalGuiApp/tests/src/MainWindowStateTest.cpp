// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "MainWindowState.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using StateEnum = MainWindowState::StateEnum;


TEST_CASE("PortClosed")
{
  const auto state = MainWindowState::portClosed();

  CHECK( state.enumState() == StateEnum::PortClosed );
  CHECK( !state.canSubmitCommand() );
  CHECK( state.canConfigurePort() );
  CHECK( state.canOpenPort() );
  CHECK( !state.canClosePort() );
  CHECK( !state.canSetDTR() );
  CHECK( !state.canSetRTS() );
  CHECK( !state.canSetBreak() );
  CHECK( !state.canSendXON() );
  CHECK( !state.canSendXOFF() );
}

TEST_CASE("PortOpen")
{
  const auto state = MainWindowState::portOpen();

  CHECK( state.enumState() == StateEnum::PortOpen );
  CHECK( state.canSubmitCommand() );
  CHECK( !state.canConfigurePort() );
  CHECK( !state.canOpenPort() );
  CHECK( state.canClosePort() );
  CHECK( state.canSetDTR() );
  CHECK( state.canSetRTS() );
  CHECK( state.canSetBreak() );
  CHECK( state.canSendXON() );
  CHECK( state.canSendXOFF() );
}
