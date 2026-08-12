// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "InterfaceList.h"
#include "Mdt/SerialPort/Device/MoxaUPort.h"
#include "Mdt/SerialPort/Platform.h"
#include <algorithm>
#include <iterator>
#include <cassert>

namespace Mdt{ namespace SerialPort{

template<typename Pred>
std::optional<InterfaceList::size_type> findIndexInInterfaceList(const std::vector<Interface> & list, Pred pred) noexcept
{
  const auto it = std::find_if(list.cbegin(), list.cend(), pred);

  if( it == list.cend() ){
    return {};
  }
  const auto d = std::distance(list.cbegin(), it);
  assert(d >= 0);

  /*
   * Can be safely casted to size_type
   * See https://stackoverflow.com/questions/49610276/length-between-iterators-in-size-type
   */
  return d;
}


InterfaceList::InterfaceList()
 : mList{Interface()}
{
}

std::optional<InterfaceList::size_type> InterfaceList::findIndexOfParameterValue(unsigned int value) const noexcept
{
  assert( canSelectInterface() );

  const auto pred = [value](const Interface & interface) -> bool {
    return interface.parameterValue() == value;
  };

  return findIndexInInterfaceList(mList, pred);
}

std::optional<InterfaceList::size_type> InterfaceList::findIndexOfStandard(InterfaceStandard standard) const noexcept
{
  const auto pred = [standard](const Interface & interface) -> bool {
    return interface.standard() == standard;
  };

  return findIndexInInterfaceList(mList, pred);
}

InterfaceList InterfaceList::fromVendorIdentifierAndProductIdentifier(quint16 vid, quint16 pid)
{
  if( Device::vendorIdentifierIsMoxa(vid) ){
    if constexpr( osIsWindows() ){
      return systemHandledOnly();
    }else{
      return fromMoxaProductIdentifier(pid);
    }
  }

  return InterfaceList();
}

InterfaceList InterfaceList::systemHandledOnly()
{
  return InterfaceList({Interface::systemHandledOnly()});
}

InterfaceList InterfaceList::fromMoxaProductIdentifier(quint16 pid)
{
  if( Device::productIdentifierIsMoxaUPort_1250_1450_1650(pid) ){
    return moxaUPort_1250_1450_1650();
  }

  return InterfaceList();
}

InterfaceList InterfaceList::moxaUPort_1250_1450_1650()
{
  return InterfaceList({
    Interface::fromStandardAndParameterValue(InterfaceStandard::RS_232, 0x00),
    Interface::fromStandardAndParameterValue(InterfaceStandard::RS_485_2W, 0x01),
    Interface::fromStandardAndParameterValue(InterfaceStandard::RS_422, 0x02),
    Interface::fromStandardAndParameterValue(InterfaceStandard::RS_485_4W, 0x03)
  });
}

InterfaceList::InterfaceList(const std::vector<Interface> & list)
 : mList(list)
{
}

}} // namespace Mdt{ namespace SerialPort{
