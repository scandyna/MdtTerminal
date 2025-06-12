// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_DEVICE_HANDLE_H
#define MDT_USB_DEVICE_HANDLE_H

#include "Mdt/Usb/LibusbRuntimeError.h"
#include "mdt_usb_export.h"
#include <libusb.h>

namespace Mdt{ namespace Usb{

  /*! \brief Wrapper around libusb_device_handle
   *
   * \sa https://libusb.sourceforge.io/api-1.0/group__libusb__dev.html
   */
  class MDT_USB_EXPORT DeviceHandle
  {
   public:

    DeviceHandle() = delete;

    /*! \brief Close this device handle
     */
    ~DeviceHandle() noexcept;

    DeviceHandle(const DeviceHandle &) = delete;
    DeviceHandle & operator=(const DeviceHandle &) = delete;

    DeviceHandle(DeviceHandle &&) = delete;
    DeviceHandle & operator=(DeviceHandle &&) = delete;

    /*! \brief Get the libus handle
     */
    libusb_device_handle *libusbHandle() const noexcept
    {
      return mHandle;
    }

    /*! \brief Open a device and obtain a device handle
     *
     * \pre \a device must be valid
     * \exception LibusbRuntimeError
     */
    static
    DeviceHandle open(libusb_device *device);

   private:

    DeviceHandle(libusb_device_handle *handle) noexcept;

    libusb_device_handle *mHandle;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_DEVICE_HANDLE_H
