// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_STRING_HELPERS_H
#define MDT_SERIAL_PORT_STRING_HELPERS_H

#include "mdt_serialport_export.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <stdexcept>

namespace Mdt{ namespace SerialPort{

  /*! \brief Returns the length of the given null-terminated byte string
   *
   * Returns 0 if \a str is a null pointer.
   *
   * Returns \a maxLength if the null character was not found
   * in the first \a maxLength bytes.
   *
   * \note the null character is not included in the length
   *
   * \sa https://en.cppreference.com/w/c/string/byte/strlen
   * \sa https://stackoverflow.com/questions/66346502/which-is-most-standard-strnlen-or-strnlen-s
   */
  MDT_SERIALPORT_EXPORT
  size_t stringLength(const char *str, size_t maxLength) noexcept;

  /*! \brief
   *
   * \todo document + implement
   */
  MDT_SERIALPORT_EXPORT
  bool stringStartsWith(const std::string & str, const char *s) noexcept;

  /*! \brief Get a uint8_t value from given string
   *
   * \pre \a str must not be empty
   * \pre \a base must be in range 0 to 36
   * \exception std::invalid_argument if no conversion could be performed
   * \exception std::out_of_range if the converted value would fall out of the range of the uint8_t
   * or if the underlying function (std::strtoul or std::strtoull) sets errno to ERANGE. 
   *
   * \sa https://en.cppreference.com/w/cpp/string/basic_string/stoul.html
   */
  MDT_SERIALPORT_EXPORT
  uint8_t uint8_t_valueFromString(const std::string & str, int base = 10);

  /*! \brief Get a uint16_t value from given string
   *
   * \pre \a str must not be empty
   * \pre \a base must be in range 0 to 36
   * \exception std::invalid_argument if no conversion could be performed
   * \exception std::out_of_range if the converted value would fall out of the range of the uint16_t
   * or if the underlying function (std::strtoul or std::strtoull) sets errno to ERANGE. 
   *
   * \sa https://en.cppreference.com/w/cpp/string/basic_string/stoul.html
   */
  MDT_SERIALPORT_EXPORT
  uint16_t uint16_t_valueFromString(const std::string & str, int base = 10);

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_STRING_HELPERS_H
