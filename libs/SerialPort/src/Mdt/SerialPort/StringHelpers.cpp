// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "StringHelpers.h"
#include <cstring>
#include <limits>
#include <cassert>


namespace Mdt{ namespace SerialPort{

size_t stringLength(const char *str, size_t maxLength) noexcept
{
  if(str == nullptr){
    return 0;
  }

  const char *pos = static_cast<const char *>( std::memchr(str, '\0', maxLength) );
  if(pos == nullptr){
    return maxLength;
  }
  assert(pos >= str);

  return static_cast<size_t>(pos - str);
}

bool stringStartsWith(const std::string & str, const char *prefix) noexcept
{
  assert(prefix != nullptr);

  const auto prefixLen = stringLength(prefix, 1001);
  assert(prefixLen > 0);
  assert(prefixLen <= 1000);

  return str.find(prefix, 0, prefixLen) == 0;
}

namespace Impl{

  template<typename T>
  T valueFromString(const std::string & str, int base, const std::string & T_name)
  {
    const unsigned long value = std::stoul(str, nullptr, base);

    if( value > std::numeric_limits<T>::max() ){
      std::string msg = str + " not fits to a " + T_name;
      throw std::out_of_range(msg);
    }

    return static_cast<T>(value);
  }

} // namespace Impl{

uint8_t uint8_t_valueFromString(const std::string & str, int base)
{
  assert( !str.empty() );
  assert( base >= 0 );
  assert( base <= 36 );

  return Impl::valueFromString<uint8_t>(str, base, "uint8_t");
}

uint16_t uint16_t_valueFromString(const std::string & str, int base)
{
  assert( !str.empty() );
  assert( base >= 0 );
  assert( base <= 36 );

  return Impl::valueFromString<uint16_t>(str, base, "uint16_t");
}

}} // namespace Mdt{ namespace SerialPort{
