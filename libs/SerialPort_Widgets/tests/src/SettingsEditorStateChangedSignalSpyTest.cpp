// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsEditorStateChangedSignalSpy.h"
#include "Mdt/SerialPort/SettingsEditorStateMachine.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;


TEST_CASE("initialState")
{
  SettingsEditorStateMachine sm;
  SettingsEditorStateChangedSignalSpy stateChangedSpy(&sm);

  CHECK( stateChangedSpy.count() == 0 );
}
