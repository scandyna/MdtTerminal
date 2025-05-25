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
#include <cassert>

namespace Mdt{ namespace Usb{

  /*! \page Usb_NumericLimits USB numeric limits
   *
   * \todo Should move to the MdtNumeric library
   *
   * \sa uint8_t_canHoldValueOf_size_t()
   * \sa uint8_t_from_size_t()
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

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_NUMERIC_LIMITS_H
