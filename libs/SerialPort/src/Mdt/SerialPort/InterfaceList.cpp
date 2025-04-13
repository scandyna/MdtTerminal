// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "InterfaceList.h"
#include "InterfaceStringFormat.h"
#include <algorithm>
#include <iterator>
#include <cassert>

namespace Mdt{ namespace SerialPort{

InterfaceList::InterfaceList()
 : mList{Interface::fromNameAndParameterValue(InterfaceStringFormat::rs232Name(), 0)}
{
}

std::optional<InterfaceList::size_type> InterfaceList::findIndexOfParameterValue(unsigned int value) const noexcept
{
  assert( canSelectInterface() );

  const auto pred = [value](const Interface & interface) -> bool {
    return interface.parameterValue() == value;
  };
  const auto it = std::find_if(mList.cbegin(), mList.cend(), pred);

  if( it == mList.cend() ){
    return {};
  }
  const auto d = std::distance(mList.cbegin(), it);
  assert(d >= 0);

  /*
   * Can be safely casted to size_type
   * See https://stackoverflow.com/questions/49610276/length-between-iterators-in-size-type
   */
  return d;
}

InterfaceList InterfaceList::fromVendorIdentifierAndProductIdentifier(quint16 vid, quint16 pid)
{
  if( vendorIdentifierIsMoxa(vid) ){
    return fromMoxaProductIdentifier(pid);
  }

  return InterfaceList();
}

bool InterfaceList::vendorIdentifierIsMoxa(quint16 vid) noexcept
{
  return vid == 0x110a;
}

InterfaceList InterfaceList::fromMoxaProductIdentifier(quint16 pid)
{
  switch(pid){
    case 0x1250:
      return moxaUPort_1250_1450_1650();
  }

  return InterfaceList();
}

InterfaceList InterfaceList::moxaUPort_1250_1450_1650()
{
  return InterfaceList({
    Interface::fromNameAndParameterValue(InterfaceStringFormat::rs232Name(), 0x00),
    Interface::fromNameAndParameterValue(InterfaceStringFormat::rs485TwoWireName(), 0x01),
    Interface::fromNameAndParameterValue(InterfaceStringFormat::rs422Name(), 0x02),
    Interface::fromNameAndParameterValue(InterfaceStringFormat::rs485FourWireName(), 0x03)
  });
}

InterfaceList::InterfaceList(const std::vector<Interface> & list)
 : mList(list)
{
}

}} // namespace Mdt{ namespace SerialPort{
