// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_CONFIG_DESCRIPTOR_H
#define MDT_USB_CONFIG_DESCRIPTOR_H

#include "Mdt/Usb/Interface.h"
#include "Mdt/Usb/LibusbRuntimeError.h"
#include "Mdt/Usb/NumericLimits.h"
#include "mdt_usb_export.h"
#include <libusb.h>
#include <cstdint>
#include <limits>
#include <vector>
#include <cassert>

namespace Mdt{ namespace Usb{

  /*! \brief Representation of the standard USB configuration descriptor
   *
   * This descriptor is documented in section 9.6.3 of the USB 3.0 specification.
   */
  class MDT_USB_EXPORT ConfigDescriptor
  {
   public:

    /// \todo deal with copy / move

    /*! \brief Get the number of interfaces supported by this configuration
     */
    uint8_t bNumInterfaces() const noexcept
    {
      return interfaceCount();
    }

    /*! \brief Get the count of interfaces
     */
    uint8_t interfaceCount() const noexcept
    {
      assert( uint8_t_canHoldValueOf_size_t( mInterfaceList.size() ) );

      return uint8_t_from_size_t( mInterfaceList.size() );
    }

    /*! \brief Get the interface at given index
     *
     * \pre \a index must be in range
     */
    const Interface & interfaceAt(uint8_t index) const noexcept
    {
      assert( index < interfaceCount() );

      return mInterfaceList[index];
    }

    /*! \brief Get a descriptor from given libusb config descriptor
     */
    static
    ConfigDescriptor fromLibusbDescriptor(const libusb_config_descriptor & descriptor) noexcept;

    /*! \brief Get a descriptor from given libusb device pointer
     *
     * \pre \a device must be a valid pointer
     * \exception LibusbRuntimeError
     */
    static
    ConfigDescriptor activeConfigFromLibusbDevicePointer(libusb_device *device);

   private:

    // explicit
    // ConfigDescriptor(const libusb_config_descriptor & descriptor) noexcept
    //  : mDescriptor(descriptor)
    // {
    // }

    /// \todo If default constructor becomes public, struct must be 0 initalized - Note: {} !
    ConfigDescriptor() noexcept = default;

    std::vector<Interface> mInterfaceList;
    // libusb_config_descriptor mDescriptor;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_CONFIG_DESCRIPTOR_H
