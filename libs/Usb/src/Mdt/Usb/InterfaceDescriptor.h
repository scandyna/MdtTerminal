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

#include "Mdt/Usb/EndpointDescriptor.h"
#include "Mdt/Usb/NumericLimits.h"
#include "mdt_usb_export.h"
#include <cstdint>
#include <libusb.h>
#include <vector>
#include <cassert>

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
      assert( uint8_t_canHoldValueOf_size_t( mEndpointList.size() ) );

      return uint8_t_from_size_t( mEndpointList.size() );
    }

    /*! \brief Get the ednpoint descriptor at given address
     *
     * \pre \a index must be in range
     */
    const EndpointDescriptor & endpointAt(uint8_t index) const noexcept
    {
      assert( index < bNumEndpoints() );

      return mEndpointList[index];
    }

    /*! \brief Get a descriptor from given libusb interface descriptor
     */
    static
    InterfaceDescriptor fromLibusbDescriptor(const libusb_interface_descriptor & descriptor) noexcept;

   private:

    InterfaceDescriptor() noexcept = default;

    std::vector<EndpointDescriptor> mEndpointList;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_INTERFACE_DESCRIPTOR_H
