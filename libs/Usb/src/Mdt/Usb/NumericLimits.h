// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_NUMERIC_LIMITS_H
#define MDT_USB_NUMERIC_LIMITS_H

#include <cstdint>
#include <limits>
#include <chrono>
#include <cassert>

namespace Mdt{ namespace Usb{

  /*! \page Usb_NumericLimits USB numeric limits
   *
   * \todo Should move to the MdtNumeric library
   *
   * \sa uint8_t_canHoldValueOf_size_t()
   * \sa uint8_t_from_size_t()
   * \sa unsigned_int_canHoldValueOf_std_chrono_milliseconds()
   * \sa unsigned_int_from_std_chrono_milliseconds()
   */

  /*! \brief Check if an uint8_t can represent given value of type std::size_t
   *
   * \todo Should move to Mdt/Numeric/Limits
   */
  inline
  constexpr
  bool uint8_t_canHoldValueOf_size_t(std::size_t s) noexcept
  {
    return s <= std::numeric_limits<uint8_t>::max();
  }

  /*! \brief Get an uint8_t from a given value of type std::size_t
   *
   * \todo Should move to Mdt/Numeric/BasicConversion
   *
   * \pre An uint8_t must be able to hold given value
   * \sa uint8_t_canHoldValueOf_size_t()
   */
  inline
  constexpr
  uint8_t uint8_t_from_size_t(std::size_t s) noexcept
  {
    assert( uint8_t_canHoldValueOf_size_t(s) );

    return static_cast<uint8_t>(s);
  }

  /*! \brief Check if an unsigned int can hold given value of type std::chrono::milliseconds
   */
  inline
  constexpr
  bool unsigned_int_canHoldValueOf_std_chrono_milliseconds(std::chrono::milliseconds d) noexcept
  {
    const auto ticks = d.count();
    if(ticks < 0){
      return false;
    }

    return ticks <= std::numeric_limits<unsigned int>::max();
  }

  /*! \brief Get an unsigned int representing the count of milliseconds of given duration
   *
   * \pre an unsigned int must be able to hold given durantion
   * \sa unsigned_int_canHoldValueOf_std_chrono_milliseconds()
   */
  inline
  constexpr
  unsigned int unsigned_int_from_std_chrono_milliseconds(std::chrono::milliseconds d) noexcept
  {
    assert( unsigned_int_canHoldValueOf_std_chrono_milliseconds(d) );

    return static_cast<unsigned int>( d.count() );
  }

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_NUMERIC_LIMITS_H
