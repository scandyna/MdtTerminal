// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Settings.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

bool Settings::baudRateHasMinimalValidity(qint32 rate) noexcept
{
  return rate > 0;
}

bool Settings::dataBitsHasMinimalValidity(QSerialPort::DataBits bits) noexcept
{
  return bits != QSerialPort::UnknownDataBits;
}

bool Settings::parityHasMinimalValidity(QSerialPort::Parity parity) noexcept
{
  return parity != QSerialPort::UnknownParity;
}

bool Settings::flowControlHasMinimalValidity(QSerialPort::FlowControl control) noexcept
{
  return control != QSerialPort::UnknownFlowControl;
}

Settings Settings::defaultSettings() noexcept
{
  Settings settings;

  settings.setBaudRate(9600);
  settings.setDataBits(QSerialPort::Data8);
  settings.setParity(QSerialPort::NoParity);
  settings.setFlowControl(QSerialPort::NoFlowControl);

  return settings;
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

}} // namespace Mdt{ namespace SerialPort{
