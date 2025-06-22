// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/Usb/ControlSetup.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"

using namespace Mdt::Usb;


TEST_CASE("defaultConstructed")
{
  ControlSetup cs;

  CHECK( cs.bmRequestTypeValue() == 0 );
}

TEST_CASE("simpleSetGet")
{
  ControlSetup cs;

  cs.setDataTransferDirection(DataTransferDirection::DeviceToHost);
  cs.setRequestType(RequestType::Class);
  cs.setRecipient(RequestRecipient::Interface);
  cs.setbRequestValue(0x10);
  cs.setwValueValue(2);
  cs.setwIndexValue(3);
  cs.setwLengthValue(4);

  CHECK( cs.bmRequestTypeValue() == 0b1010'0001 );
  CHECK( cs.bRequestValue() == 0x10 );
  CHECK( cs.wValueValue() == 2 );
  CHECK( cs.wIndexValue() == 3 );
  CHECK( cs.wLengthValue() == 4 );
}
