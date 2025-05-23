// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_INTERFACE_DESCRIPTOR_H
#define MDT_USB_INTERFACE_DESCRIPTOR_H

#include "mdt_usb_export.h"
#include <cstdint>
#include <libusb.h>

namespace Mdt{ namespace Usb{

  /*! \brief Representation of the standard USB interface descriptor
   *
   * This descriptor is documented in section 9.6.5 of the USB 3.0 specification.
   * All multiple-byte fields are represented in host-endian format. 
   */
  class MDT_USB_EXPORT InterfaceDescriptor
  {
   public:

    /// \todo deal with copy / move

    /*! \brief Get the number of endpoints used by this interface (excluding the control endpoint)
     */
    uint8_t bNumEndpoints() const noexcept
    {
      return mbNumEndpoints;
    }

    /*! \brief Get a descriptor from given libusb interface descriptor
     */
    static
    InterfaceDescriptor fromLibusbDescriptor(const libusb_interface_descriptor & descriptor) noexcept;

   private:

    InterfaceDescriptor() noexcept = default;

    uint8_t mbNumEndpoints = 0;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_INTERFACE_DESCRIPTOR_H
