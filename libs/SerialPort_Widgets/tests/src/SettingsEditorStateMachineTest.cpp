// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SettingsEditorStateMachine.h"
#include "SettingsEditorStateChangedSignalSpy.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort;
using StateEnum = SettingsEditorState::StateEnum;


TEST_CASE("initialState")
{
  SettingsEditorStateMachine sm;
  SettingsEditorStateChangedSignalSpy stateChangedSpy(&sm);

  CHECK( sm.currentEnumState() == StateEnum::Incomplete );
  CHECK( stateChangedSpy.count() == 0 );

  sm.start();
  CHECK( sm.currentEnumState() == StateEnum::Incomplete );
  REQUIRE( stateChangedSpy.count() == 1 );
  CHECK( stateChangedSpy.enumStateAt(0) == StateEnum::Incomplete );
}

TEST_CASE("Incomplete")
{
  SettingsEditorStateMachine sm;
  SettingsEditorStateChangedSignalSpy stateChangedSpy(&sm);
  sm.start();
  stateChangedSpy.clear();
  REQUIRE( sm.currentEnumState() == StateEnum::Incomplete );
  REQUIRE( stateChangedSpy.count() == 0 );

  SECTION("settingsComplete event: transition to Complete")
  {
    sm.setSettingsCompleteEvent();

    REQUIRE( sm.currentEnumState() == StateEnum::Complete );
    REQUIRE( stateChangedSpy.count() == 1 );
    CHECK( stateChangedSpy.enumStateAt(0) == StateEnum::Complete );
  }

  SECTION("startFetchingSystemInfo event: transition to FetchingSystemInfo")
  {
    sm.setStartFetchingSystemInfoEvent();

    REQUIRE( sm.currentEnumState() == StateEnum::FetchingSystemInfo );
    REQUIRE( stateChangedSpy.count() == 1 );
    CHECK( stateChangedSpy.enumStateAt(0) == StateEnum::FetchingSystemInfo );
  }
}

TEST_CASE("Complete")
{
  SettingsEditorStateMachine sm;
  SettingsEditorStateChangedSignalSpy stateChangedSpy(&sm);
  sm.start();
  sm.setSettingsCompleteEvent();
  stateChangedSpy.clear();
  REQUIRE( sm.currentEnumState() == StateEnum::Complete );
  REQUIRE( stateChangedSpy.count() == 0 );

  SECTION("settingsIncomplete event: transition to Incomplete")
  {
    sm.setSettingsIncompleteEvent();

    REQUIRE( sm.currentEnumState() == StateEnum::Incomplete );
    REQUIRE( stateChangedSpy.count() == 1 );
    CHECK( stateChangedSpy.enumStateAt(0) == StateEnum::Incomplete );
  }

  SECTION("startFetchingSystemInfo event: transition to FetchingSystemInfo")
  {
    sm.setStartFetchingSystemInfoEvent();

    REQUIRE( sm.currentEnumState() == StateEnum::FetchingSystemInfo );
    REQUIRE( stateChangedSpy.count() == 1 );
    CHECK( stateChangedSpy.enumStateAt(0) == StateEnum::FetchingSystemInfo );
  }
}

TEST_CASE("FetchingSystemInfo")
{
  SettingsEditorStateMachine sm;
  SettingsEditorStateChangedSignalSpy stateChangedSpy(&sm);
  sm.start();
  sm.setStartFetchingSystemInfoEvent();
  stateChangedSpy.clear();
  REQUIRE( sm.currentEnumState() == StateEnum::FetchingSystemInfo );
  REQUIRE( stateChangedSpy.count() == 0 );

  SECTION("settingsIncomplete event: transition to Incomplete")
  {
    sm.setSettingsIncompleteEvent();

    REQUIRE( sm.currentEnumState() == StateEnum::Incomplete );
    REQUIRE( stateChangedSpy.count() == 1 );
    CHECK( stateChangedSpy.enumStateAt(0) == StateEnum::Incomplete );
  }

  SECTION("settingsComplete event: transition to Complete")
  {
    sm.setSettingsCompleteEvent();

    REQUIRE( sm.currentEnumState() == StateEnum::Complete );
    REQUIRE( stateChangedSpy.count() == 1 );
    CHECK( stateChangedSpy.enumStateAt(0) == StateEnum::Complete );
  }
}
