// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_LIBUSB_DEVICE_LIST_H
#define MDT_USB_LIBUSB_DEVICE_LIST_H

#include "mdt_usb_export.h"
#include <libusb.h>
#include <cstddef>
#include <cassert>


namespace Mdt{ namespace Usb{

  /*! \brief A wrapper to a list of libusb device
   *
   * To create a list, use DeviceEnumerator.
   *
   * \warning This list must exist as long as a pointer to libusb_device is used.
   * When a device has been open, and no pointer to libusb_device is used,
   * this list can be destroyed.
   *
   * \sa DeviceEnumerator
   * \sa https://libusb.sourceforge.io/api-1.0/group__libusb__dev.html
   */
  class MDT_USB_EXPORT LibusbDeviceList
  {
    friend class DeviceEnumerator;

   public:

    /*! \brief Free this device list
     */
    ~LibusbDeviceList() noexcept;

    LibusbDeviceList(const LibusbDeviceList &) = delete;
    LibusbDeviceList & operator=(const LibusbDeviceList &) = delete;

    /*! \brief Move construct a list from \a other
     */
    LibusbDeviceList(LibusbDeviceList && other) noexcept
     : mCount(other.mCount),
       mList(other.mList)
    {
      other.mCount = 0;
      other.mList = nullptr;
    }

    LibusbDeviceList & operator=(LibusbDeviceList &&) = delete;

    /*! \brief Get the count of devices
     */
    size_t count() const noexcept
    {
      return mCount;
    }

    /*! \brief Get the device pointer at given index
     *
     * \pre \a index must be in range of this list
     */
    libusb_device *libusbDevicePointerAt(size_t index) const noexcept
    {
      assert( index < count() );

      return mList[index];
    }

   private:

    LibusbDeviceList() noexcept = default;

    size_t mCount = 0;
    libusb_device **mList = nullptr;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_LIBUSB_DEVICE_LIST_H
