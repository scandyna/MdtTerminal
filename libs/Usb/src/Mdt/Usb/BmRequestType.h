// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_BM_REQUEST_TYPE_H
#define MDT_USB_BM_REQUEST_TYPE_H

#include "Mdt/Usb/BitManipulationHelpers.h"
#include "mdt_usb_export.h"
#include <cstdint>

namespace Mdt{ namespace Usb{

  /*! \brief Data transfer direction
   *
   * Refers to the bit D7 of the bmRequestType
   *
   * \sa USB 3.2 specification §9.3
   */
  enum class DataTransferDirection : uint8_t
  {
    HostToDevice = 0x00,  /*!< Host to device */
    DeviceToHost = 0x80   /*!< Device to host */
  };

  /*! \brief Mask corresponding to DataTransferDirection
   */
  constexpr
  uint8_t DataTransferDirectionMask = 0b1000'0000;


  /*! \brief Request type
   *
   * Refers to bits D6...5 of the bmRequestType
   *
   * \sa USB 3.2 specification §9.3
   */
  enum class RequestType : uint8_t
  {
    Standard = 0,       /*!< Standard */
    Class = (1 << 5),   /*!< Class */
    Vendor = (2 << 5),  /*!< Vendor */
    Reserved = (3 << 5) /*!< Reserved */
  };

  /*! \brief Mask corresponding to RequestType
   */
  constexpr
  uint8_t RequestTypeMask = 0b0110'0000;

  /*! \brief Request recipient
   *
   * Refers to bits D4...0 of the bmRequestType
   *
   * Values from 4 to 30 are reserved.
   *
   * \sa USB 3.2 specification §9.3
   */
  enum class RequestRecipient : uint8_t
  {
    Device = 0,         /*!< Device */
    Interface = 1,      /*!< Interface */
    Endpoint = 2,       /*!< Endpoint */
    Other = 3,          /*!< Other */
    VendorSpecific = 31 /*!< Vendor specific */
  };

  /*! \brief Mask corresponding to RequestRecipient
   */
  constexpr
  uint8_t RequestRecipientMask = 0b0001'1111;

  /*! \brief Helper class around bmRequestType
   *
   * \sa USB 3.2 specification §9.3
   */
  class MDT_USB_EXPORT BmRequestType
  {
   public:

    /*! \brief Set data transfer direction
     *
     * Acts on bit D7 of the bmRequestType
     */
    constexpr
    void setDataTransferDirection(DataTransferDirection direction) noexcept
    {
      mValue = applyFlags(mValue, DataTransferDirectionMask, direction);
    }

    /*! \brief Get data transfer direction
     *
     * \sa setDataTransferDirection()
     */
    constexpr
    DataTransferDirection dataTransferDirection() const noexcept
    {
      return static_cast<DataTransferDirection>(mValue & DataTransferDirectionMask);
    }

    /*! \brief Set the type
     *
     * Acts on bits D6...5 of the bmRequestType
     */
    constexpr
    void setType(RequestType type) noexcept
    {
      mValue = applyFlags(mValue, RequestTypeMask, type);
    }

    /*! \brief Get the type
     *
     * \sa setType()
     */
    constexpr
    RequestType type() const noexcept
    {
      return static_cast<RequestType>(mValue & RequestTypeMask);
    }

    /*! \brief Set the recipient
     *
     * Acts on bits D4...0 of the bmRequestType
     */
    constexpr
    void setRecipient(RequestRecipient recipient) noexcept
    {
      mValue = applyFlags(mValue, RequestRecipientMask, recipient);
    }

    /*! \brief Get the recipient
     *
     * \sa setRecipient()
     */
    constexpr
    RequestRecipient recipient() const noexcept
    {
      return static_cast<RequestRecipient>(mValue & RequestRecipientMask);
    }

    /*! \brief Set the value for this bmRequestType
     */
    constexpr
    void setValue(uint8_t value) noexcept
    {
      mValue = value;
    }

    /*! \brief Get the value of this bmRequestType
     */
    constexpr
    uint8_t value() const noexcept
    {
      return mValue;
    }

   private:

    uint8_t mValue = 0;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_BM_REQUEST_TYPE_H
