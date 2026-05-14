// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortInfo.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

PortInfo PortInfo::fromQSerialPortInfo(const QSerialPortInfo & portInfo)
{
  assert( !portInfo.isNull() );

  PortInfo pi( portInfo.portName(), portInfo.systemLocation() );
  pi.setDescription( portInfo.description() );
  pi.setManufacturer( portInfo.manufacturer() );
  pi.setSerialNumber( portInfo.serialNumber() );
  if( portInfo.hasVendorIdentifier() ){
    pi.setVendorIdentifier( portInfo.vendorIdentifier() );
  }
  if( portInfo.hasProductIdentifier() ){
    pi.setProductIdentifier( portInfo.productIdentifier() );
  }

  return pi;
}

void PortInfo::setDescription(const QString & description)
{
  mDescription = description;
}

void PortInfo::setManufacturer(const QString & manufacturer)
{
  mManufacturer = manufacturer;
}

void PortInfo::setSerialNumber(const QString & sn)
{
  mSerialNumber = sn;
}

void PortInfo::setVendorIdentifier(uint16_t vid)
{
  mVendorIdentifier = vid;
}

void PortInfo::setProductIdentifier(uint16_t pid)
{
  mProductIdentifier = pid;
}

PortInfo::PortInfo(const QString & portName, const QString & systemLocation) noexcept
 : mPortName(portName),
   mSystemLocation(systemLocation)
{
  assert( !mPortName.trimmed().isEmpty() );
  assert( !mSystemLocation.trimmed().isEmpty() );
}

}} // namespace Mdt{ namespace SerialPort{
