// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_DEVICE_DESCRIPTOR_H
#define MDT_USB_DEVICE_DESCRIPTOR_H

#include "mdt_usb_export.h"
#include <libusb.h>

namespace Mdt{ namespace Usb{

  /*! \brief Helper class around libusb_device_descriptor
   *
   * This descriptor is documented in section 9.6.1 of the USB 3.0 specification.
   */
  class MDT_USB_EXPORT DeviceDescriptor
  {
   public:

    /// \todo If default constructor, struct must be 0 initalized - Note: {} !
    DeviceDescriptor() = delete;

    /*! \brief Copy construct a descriptor from other
     */
    DeviceDescriptor(const DeviceDescriptor & other) noexcept = default;

    /*! \brief Copy assign other to this descriptor
     */
    DeviceDescriptor & operator=(const DeviceDescriptor & other) noexcept = default;

    /*! \brief Move construct a descriptor from other
     */
    DeviceDescriptor(DeviceDescriptor && other) noexcept = default;

    /*! \brief Move assign other to this descriptor
     */
    DeviceDescriptor & operator=(DeviceDescriptor && other) noexcept = default;

    /*! \brief Get the libusb descriptor
     */
    const libusb_device_descriptor & libusbDescriptor() const noexcept
    {
      return mDescriptor;
    }

    /*! \brief Access the libusb descriptor for mutation
     */
    libusb_device_descriptor & libusbDescriptorMutable() noexcept
    {
      return mDescriptor;
    }

    /*! \brief Get a descriptor from given libusb descriptor
     */
    static
    DeviceDescriptor fromLibusbDescriptor(const libusb_device_descriptor & descriptor) noexcept
    {
      return DeviceDescriptor(descriptor);
    }

    /*! \brief Get a descriptor from given libusb device pointer
     *
     * \pre \a device must be a valid pointer
     */
    static
    DeviceDescriptor fromLibusbDevicePointer(libusb_device *device) noexcept;

   private:

    DeviceDescriptor(const libusb_device_descriptor & descriptor) noexcept
     : mDescriptor(descriptor)
    {
    }

    libusb_device_descriptor mDescriptor;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_DEVICE_DESCRIPTOR_H
