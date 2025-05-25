// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_ENDPOINT_DESCRIPTOR_H
#define MDT_USB_ENDPOINT_DESCRIPTOR_H

#include "mdt_usb_export.h"
#include <libusb.h>
#include <cstdint>

namespace Mdt{ namespace Usb{

  /*! \brief Representation of the standard USB endpoint descriptor
   *
   * This descriptor is documented in section 9.6.6 of the USB 3.0 specification.
   * All multiple-byte fields are represented in host-endian format.
   */
  class MDT_USB_EXPORT EndpointDescriptor
  {
   public:

    /// \todo deal with copy / move

    /*! \brief Get the address of the endpoint
     */
    uint8_t bEndpointAddress() const noexcept
    {
      return mbEndpointAddress;
    }
 
    /*! \brief Get a descriptor from given libusb endpoint descriptor
     */
    static
    EndpointDescriptor fromLibusbDescriptor(const libusb_endpoint_descriptor & descriptor) noexcept;

   private:

    EndpointDescriptor() noexcept = default;

    uint8_t mbEndpointAddress = 0;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_ENDPOINT_DESCRIPTOR_H
