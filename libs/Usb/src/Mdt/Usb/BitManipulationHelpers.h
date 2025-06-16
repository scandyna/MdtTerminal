// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_BIT_MANIPULATION_HELPERS_H
#define MDT_USB_BIT_MANIPULATION_HELPERS_H

#include <type_traits>

namespace Mdt{ namespace Usb{

  /*
   *   value: 1010'1000
   *   mask:  0000'0000
   *  ~mask:  1111'1111
   *
   *   value: 1010'1000
   *  ~mask:  1111'1111
   * ------------------
   *    AND:  1010'1000
   *
   *  ~value: 0101'0111
   *   mask:  0000'0000
   * ------------------
   *     AND: 0000'0000
   *       ~: 1010'1000
   *
   *   value: 0010'1000
   *
   *     OR:  1010'1000
   *
   *
   * === Set a bit ===
   * 
   *
   * === Clear a bit ===
   *
   *
   * === Set or clear a bit regarding flags /  mask ===
   *
   * 1) Get current value with the bits regarding mask set to 0
   * 2) Set bits: value = newValue | flags
   *
   * mask  = 0b1000'0000
   * flags = 0b0000'0000
   *
   * tmpValue = value & ~mask; // 0b0xxx'xxxx
   * value = tmpValue | flags;
   *
   * value:    0b1000'1010
   * ~mask:    0b0111'1111
   * ---AND---------------
   * tmpValue: 0b0000'1010
   * flags:    0b0000'0000
   * ---OR-----------------
   * value:    0b0000'1010
   *
   *
   * value:    0b1000'1010
   * mask:     0b1000'0000
   * --OR-----------------
   * tmpValue: 0b1000'1010
   * flags:    0b0000'0000
   * --OR------------------
   * value:    0b1000'1010  :-(
   *
   * NOTE: try with ~mask !
   * 
   *
   */

  /*! \brief Apply flags to a value
   *
   * Returns given value with the given flags applyed, using given mask.
   *
   * Sets the bits in \a value to 1 or 0 regarding given \a flags and \a mask .
   *
   * \note \a flags can be an enum
   *
   * Example for a single bit, D7, on a uint8_t:
   * \code
   * enum class DataTransferDirection : uint8_t
   * {
   *   HostToDevice = 0b0000'0000,
   *   DeviceToHost = 0b1000'0000
   * };
   *
   * constexpr
   * uint8_t DataTransferDirectionMask = 0b1000'0000;
   * \endcode
   *
   * To set the bit D7 to 1:
   * \code
   * uint8_t bmRequestType = 0b0000'1010;
   *
   * bmRequestType = applyFlags(bmRequestType, DataTransferDirectionMask, DataTransferDirection::DeviceToHost);
   * // bmRequestType: 0b1000'1010
   * \endcode
   *
   * We can set D7 to 0 the same way:
   * \code
   * uint8_t bmRequestType = 0b1000'1010;
   *
   * bmRequestType = applyFlags(bmRequestType, DataTransferDirectionMask, DataTransferDirection::HostToDevice);
   * // bmRequestType: 0b0000'1010
   * \endcode
   *
   * If D7 was already 0, it will not change:
   *
   * \code
   * uint8_t bmRequestType = 0b0000'1010;
   *
   * bmRequestType = applyFlags(bmRequestType, DataTransferDirectionMask, DataTransferDirection::HostToDevice);
   * // bmRequestType: 0b0000'1010
   * \endcode
   *
   *
   * Implementation.
   *
   * Despite this function represents a well known pattern,
   * I did not found the solution easily, and I am not aware of an existing helper in the STL.
   * For single bit manipulations, std::bitset can be a good solution.
   * But here, we also need to be able to manipulate multiple bits to represent a value
   * (ex: bit D6 and D5 represents a value from 0 to 3).
   * So here are some informations about what's going on.
   *
   * To set a bit, we can apply value OR bit7Mask:
   * \code
   * value:    0b0000'1010
   * bit7Mask: 0b1000'0000
   *      OR   -----------
   *           0b1000'1010
   * \endcode
   *
   * To clear a bit, we can apply value AND ~bit7Mask:
   * \code
   *  value:    0b1000'1010
   * ~bit7Mask: 0b0111'1111
   *     AND    -----------
   *            0b0000'1010
   * \endcode
   *
   * If we want to apply some flags to a value,
   * i.e. set or clear bits in value dependending on given flags,
   * things are a bit different.
   * We don't want to check every bit in flags to determin
   * if we have to set or clear the bit in the value.
   *
   * Here we need 2 things:
   * - flags we want to apply (ex: 0b1000'0000)
   * - a mask that tells us which bits are concerned by the flags (ex: 0b1000'0000)
   *
   * Now we can use the mask to give us a temp value
   * that will have the bits we have to manipulate to 0,
   * and all others as they are in given value.
   * Here, if we use the temp value, we don't have to choose
   * to set or clear bits: we simply set the interesting ones.
   *
   * Example that acts on bits 7, 6 and 5:
   * \code
   * value:    0b1000'1010
   * ~mask:    0b0001'1111
   *   AND  --------------
   * tmpValue: 0b0000'1010
   * flags:    0b0100'0000
   *    OR: --------------
   * result:   0b0100'1010
   * \endcode
   *
   * Here we have set bit 7 to 0, bit 6 to 1 and bit 5 stays 0.
   *
   * \pre T must be an unsigned integer type
   * \pre If Flags is an enum, its underlying type must be the same as T.
   * Otherwise, Flags must be the same type as T.
   * \pre Flags must represent the same underlying type as T
   */
  template<typename T, typename Flags>
  constexpr
  T applyFlags(T value, T mask, Flags flags) noexcept
  {
    static_assert( std::is_unsigned_v<T>, "Mdt::Usb::applyFlags() requires T be an unsigned arithmetic type" );
    if constexpr(std::is_enum_v<Flags>){
      static_assert( std::is_same_v<std::underlying_type_t<Flags>, T>, "Mdt::Usb::applyFlags() requires that the underlying type of Flags be the same as T" );
    }else{
      static_assert( std::is_same_v<Flags, T>, "Mdt::Usb::applyFlags() requires that the underlying type of Flags be the same as T" );
    }

    return static_cast<T>(value & ~mask) | static_cast<T>(flags);
  }

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_BIT_MANIPULATION_HELPERS_H
