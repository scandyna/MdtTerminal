// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "TestPortInfo.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace TestLib{

void TestPortInfo::setDescription(const QString & description)
{
  PortInfo::setDescription(description);
}

void TestPortInfo::setManufacturer(const QString & manufacturer)
{
  PortInfo::setManufacturer(manufacturer);
}

void TestPortInfo::setSerialNumber(const QString & sn)
{
  PortInfo::setSerialNumber(sn);
}

void TestPortInfo::setVendorIdentifier(uint16_t vid)
{
  PortInfo::setVendorIdentifier(vid);
}

void TestPortInfo::setProductIdentifier(uint16_t pid)
{
  PortInfo::setProductIdentifier(pid);
}

TestPortInfo TestPortInfo::fromPortNameAndSystemLocation(const QString & portName, const QString & systemLocation) noexcept
{
  assert( !portName.trimmed().isEmpty() );
  assert( !systemLocation.trimmed().isEmpty() );

  return TestPortInfo(portName, systemLocation);
}

TestPortInfo::TestPortInfo(const QString & portName, const QString & systemLocation) noexcept
 : PortInfo(portName, systemLocation)
{
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
