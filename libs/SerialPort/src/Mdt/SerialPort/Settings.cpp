// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Settings.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

bool Settings::baudRateHasMinimalValidity(qint32 rate) noexcept
{
  return rate > 0;
}

bool Settings::dataBitsHasMinimalValidity(QSerialPort::DataBits /*bits*/) noexcept
{
  return true;
}

bool Settings::parityHasMinimalValidity(QSerialPort::Parity /*parity*/) noexcept
{
  return true;
}

bool Settings::flowControlHasMinimalValidity(QSerialPort::FlowControl /*control*/) noexcept
{
  return true;
}

bool Settings::stopBitsHasMinimalValidity(QSerialPort::StopBits bits) noexcept
{
  if(bits == QSerialPort::OneAndHalfStop){
    return oneAndHalfStopBitsIsSupported();
  }
  return true;
}

Settings Settings::defaultSettings() noexcept
{
  return Settings{};
}

Settings Settings::defaultSettingsWithPortInfo(const PortInfo & portInfo) noexcept
{
  return Settings(portInfo);
}

Settings::Settings(const PortInfo & portInfo) noexcept
 : mPortInfo(portInfo)
{
}

void Settings::setPortInfo(const PortInfo & portInfo) noexcept
{
  mPortInfo = portInfo;
}

void Settings::setBaudRate(qint32 rate) noexcept
{
  assert( baudRateHasMinimalValidity(rate) );

  mBaudRate = rate;
}

void Settings::setDataBits(QSerialPort::DataBits bits) noexcept
{
  assert( dataBitsHasMinimalValidity(bits) );

  mDataBits = bits;
}

void Settings::setParity(QSerialPort::Parity parity) noexcept
{
  assert( parityHasMinimalValidity(parity) );

  mParity = parity;
}

void Settings::setFlowControl(QSerialPort::FlowControl control) noexcept
{
  assert( flowControlHasMinimalValidity(control) );

  mFlowControl = control;
}

void Settings::setStopBits(QSerialPort::StopBits bits) noexcept
{
  assert( stopBitsHasMinimalValidity(bits) );

  mStopBits = bits;
}

void Settings::setInterface(const Interface & interface) noexcept
{
  mInterface = interface;
}

void Settings::setSendByteByByteSettings(const SendByteByByteSettings & s) noexcept
{
  mSendByteByByteSettings = s;
}

}} // namespace Mdt{ namespace SerialPort{
