// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_INTERFACE_H
#define MDT_USB_INTERFACE_H

#include "Mdt/Usb/InterfaceDescriptor.h"
#include "mdt_usb_export.h"
#include <libusb.h>
#include <cstddef>
#include <vector>
#include <cassert>

namespace Mdt{ namespace Usb{

  /*! \brief A collection of alternate settings for a particular USB interface
   */
  class MDT_USB_EXPORT Interface
  {
   public:

    /// \todo deal with copy / move

    /*! \brief Get the count of alternate settings
     */
    size_t alternateSettingsCount() const noexcept
    {
      return mAlternateSettings.size();
    }

    /*! \brief Get the interface descriptor for given alternate setting index
     *
     * \pre \a index must be in range
     */
    const InterfaceDescriptor & alternateSettingAt(size_t index) const noexcept
    {
      assert( index < alternateSettingsCount() );

      return mAlternateSettings[index];
    }

    /*! \brief Get an interface from given libusb interface
     */
    static
    Interface fromLibusbInterface(const libusb_interface & interface) noexcept;

   private:

    Interface() noexcept = default;

    std::vector<InterfaceDescriptor> mAlternateSettings;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_INTERFACE_H
