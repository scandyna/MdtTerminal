// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/TestLib/PinoutSignalUiStateChangedSignalSpy.h"
#include "Mdt/SerialPort/TestLib/TestPinoutSignalsUiController.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::SerialPort::TestLib;


TEST_CASE("initialState")
{
  TestPinoutSignalsUiController psc;
  PinoutSignalUiStateChangedSignalSpy receiveDataChangedSpy(&psc, &TestPinoutSignalsUiController::receiveDataChanged);

  CHECK( receiveDataChangedSpy.count() == 0 );
}
