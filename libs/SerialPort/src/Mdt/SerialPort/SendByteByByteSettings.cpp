// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SendByteByByteSettings.h"

using namespace std::chrono_literals;

namespace Mdt{ namespace SerialPort{

SendByteByByteSettings SendByteByByteSettings::disabled() noexcept
{
  return SendByteByByteSettings();
}

SendByteByByteSettings SendByteByByteSettings::enabledWithInterval(std::chrono::milliseconds interval) noexcept
{
  assert( intervalIsValid(interval) );

  return SendByteByByteSettings(interval);
}

SendByteByByteSettings SendByteByByteSettings::enabledWithRawIntervalInMilliseconds(int interval) noexcept
{
  assert( rawIntervalInMillisecondsIsValid(interval) );

  return enabledWithInterval( std::chrono::milliseconds(interval) );
}

bool SendByteByByteSettings::intervalIsValid(std::chrono::milliseconds interval) noexcept
{
  if( interval < minimumInterval() ){
    return false;
  }
  if( interval > maximumInterval() ){
    return false;
  }

  return true;
}

bool SendByteByByteSettings::rawIntervalInMillisecondsIsValid(int interval) noexcept
{
  return intervalIsValid( std::chrono::milliseconds(interval) );
}

std::chrono::milliseconds SendByteByByteSettings::minimumInterval() noexcept
{
  return 1ms;
}

std::chrono::milliseconds SendByteByByteSettings::maximumInterval() noexcept
{
  return 500ms;
}

int SendByteByByteSettings::minimumRawIntervalInMilliseconds() noexcept
{
  return static_cast<int>( minimumInterval().count() );
}

int SendByteByByteSettings::maximumRawIntervalInMilliseconds() noexcept
{
  return static_cast<int>( maximumInterval().count() );
}

}} // namespace Mdt{ namespace SerialPort{
