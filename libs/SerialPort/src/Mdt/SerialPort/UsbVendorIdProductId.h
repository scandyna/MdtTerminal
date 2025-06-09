// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_USB_VENDOR_ID_PRODUCT_ID_H
#define MDT_SERIAL_PORT_USB_VENDOR_ID_PRODUCT_ID_H

#include "mdt_serialport_export.h"
#include <cstdint>

namespace Mdt{ namespace SerialPort{

  /*! \brief USB vendor ID and product ID
   *
   * \sa https://www.usb.org/developers
   * \sa http://www.linux-usb.org/usb.ids
   */
  struct MDT_SERIALPORT_EXPORT UsbVendorIdProductId
  {
    uint16_t vid = 0;
    uint16_t pid = 0;

    /*! \brief Check if \a a and \a b are equal
     */
    friend
    bool operator==(const UsbVendorIdProductId & a, const UsbVendorIdProductId & b) noexcept
    {
      if(a.vid != b.vid){
        return false;
      }
      if(a.pid != b.pid){
        return false;
      }

      return true;
    }

    /*! \brief Check if \a a and \a b differs
     */
    friend
    bool operator!=(const UsbVendorIdProductId & a, const UsbVendorIdProductId & b) noexcept
    {
      return !(a == b);
    }
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_USB_VENDOR_ID_PRODUCT_ID_H
