// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "MainWindowStateMachine.h"
#include "MainWindowStateChangedSignalSpy.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using StateEnum = MainWindowState::StateEnum;


class TestMainWindowStateMachine : public MainWindowStateMachine
{
 public:

  MainWindowState::StateEnum currentEnumState() const noexcept
  {
    return MainWindowStateMachine::currentEnumState();
  }
};


TEST_CASE("initialState")
{
  TestMainWindowStateMachine sm;
  MainWindowStateChangedSignalSpy stateChangedSpy(&sm);

  CHECK( sm.currentEnumState() == StateEnum::PortClosed );
  CHECK( stateChangedSpy.count() == 0 );

  sm.start();
  CHECK( sm.currentEnumState() == StateEnum::PortClosed );
  REQUIRE( stateChangedSpy.count() == 1 );
  CHECK( stateChangedSpy.enumStateAt(0) == StateEnum::PortClosed );
}

TEST_CASE("PortClosed")
{
  TestMainWindowStateMachine sm;
  MainWindowStateChangedSignalSpy stateChangedSpy(&sm);
  sm.start();
  stateChangedSpy.clear();
  REQUIRE( sm.currentEnumState() == StateEnum::PortClosed );
  REQUIRE( stateChangedSpy.count() == 0 );

  SECTION("portOpen event : transition to PortOpen")
  {
    sm.setPortOpenEvent();

    CHECK( sm.currentEnumState() == StateEnum::PortOpen );
    REQUIRE( stateChangedSpy.count() == 1 );
    CHECK( stateChangedSpy.enumStateAt(0) == StateEnum::PortOpen );
  }
}

TEST_CASE("PortOpen")
{
  TestMainWindowStateMachine sm;
  MainWindowStateChangedSignalSpy stateChangedSpy(&sm);
  sm.start();
  sm.setPortOpenEvent();
  stateChangedSpy.clear();
  REQUIRE( sm.currentEnumState() == StateEnum::PortOpen );
  REQUIRE( stateChangedSpy.count() == 0 );

  SECTION("portClosed event : transition to PortClosed")
  {
    sm.setPortClosedEvent();

    CHECK( sm.currentEnumState() == StateEnum::PortClosed );
    REQUIRE( stateChangedSpy.count() == 1 );
    CHECK( stateChangedSpy.enumStateAt(0) == StateEnum::PortClosed );
  }
}
