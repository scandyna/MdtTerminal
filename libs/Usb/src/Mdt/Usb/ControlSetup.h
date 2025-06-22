// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_CONTROL_SETUP_H
#define MDT_USB_CONTROL_SETUP_H

#include "Mdt/Usb/BmRequestType.h"
#include "mdt_usb_export.h"
#include <cstdint>

namespace Mdt{ namespace Usb{

  /*! \brief Setup packet for control transfers
   *
   * Contains the same members as libusb_control_setup.
   * This ControlSetup is available to avoid confusions with libusb_control_setup
   * (see below).
   *
   * In the libusb API, the multi-byte control setup fields (wValue, wIndex and wLength)
   * must be given in the endianness of the USB bus (little-endian).
   *
   * This ControlSetup excepts host endianness.
   * libusb helpers will be used to do the conversions if needed.
   *
   * \sa https://libusb.sourceforge.io/api-1.0/structlibusb__control__setup.html
   * \sa https://libusb.sourceforge.io/api-1.0/group__libusb__asyncio.html
   * \sa USB 3.2 specification §9.3
   */
  class MDT_USB_EXPORT ControlSetup
  {
   public:

    /*! \brief Set data transfer direction
     *
     * Acts on bit D7 of the bmRequestType
     */
    constexpr
    void setDataTransferDirection(DataTransferDirection direction) noexcept
    {
      mBmRequestType.setDataTransferDirection(direction);
    }

    /*! \brief Set the type
     *
     * Acts on bits D6...5 of the bmRequestType
     */
    constexpr
    void setRequestType(RequestType type) noexcept
    {
      mBmRequestType.setType(type);
    }

    /*! \brief Set the recipient
     *
     * Acts on bits D4...0 of the bmRequestType
     */
    constexpr
    void setRecipient(RequestRecipient recipient) noexcept
    {
      mBmRequestType.setRecipient(recipient);
    }

    /*! \brief Get the bmRequestType
     */
    constexpr
    const BmRequestType & bmRequestType() const noexcept
    {
      return mBmRequestType;
    }

    /*! \brief Get the bmRequestType value
     */
    constexpr
    uint8_t bmRequestTypeValue() const noexcept
    {
      return mBmRequestType.value();
    }

    /*! \brief Set the bRequest value
     */
    constexpr
    void setbRequestValue(uint8_t value) noexcept
    {
      m_bRequest = value;
    }

    /*! \brief Get the bRequest value
     */
    constexpr
    uint8_t bRequestValue() const noexcept
    {
      return m_bRequest;
    }

    /*! \brief Set the wValue
     */
    constexpr
    void setwValueValue(uint16_t value) noexcept
    {
      m_wValue = value;
    }

    /*! \brief Get the wValue
     */
    constexpr
    uint16_t wValueValue() const noexcept
    {
      return m_wValue;
    }

    /*! \brief Set the wIndex
     */
    constexpr
    void setwIndexValue(uint16_t value) noexcept
    {
      m_wIndex = value;
    }

    /*! \brief Get the wIndex
     */
    constexpr
    uint16_t wIndexValue() const noexcept
    {
      return m_wIndex;
    }

    /*! \brief Set the wLength
     */
    constexpr
    void setwLengthValue(uint16_t value) noexcept
    {
      m_wLength = value;
    }

    /*! \brief Get the wLength
     */
    constexpr
    uint16_t wLengthValue() const noexcept
    {
      return m_wLength;
    }

   private:

    BmRequestType mBmRequestType;
    uint8_t m_bRequest = 0;
    uint16_t m_wValue = 0;
    uint16_t m_wIndex = 0;
    uint16_t m_wLength = 0;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_CONTROL_SETUP_H
