// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_LIBUSB_ERROR_H
#define MDT_USB_LIBUSB_ERROR_H

#include "mdt_usb_export.h"
#include <QString>
#include <libusb.h>

namespace Mdt{ namespace Usb{

  /*! \brief Helper class around libusb_error
   *
   * \note This is not an exception class
   * \sa LibusbRuntimeError
   */
  class MDT_USB_EXPORT LibusbError
  {
   public:

    /*! \brief Get a libusb_error from given code
     */
    static
    libusb_error errorFromInt(int code) noexcept
    {
      return static_cast<libusb_error>(code);
    }

    /*! \brief Get a QString reprentation of given libusb_error
     */
    static
    QString errorNameFromInt(int code) noexcept;

    /*! \brief Get an error string, that gan be displayed to the user
     */
    static
    QString strerror(libusb_error code) noexcept
    {
      /*
       * libusb_strerror() return UTF-8
       * We must not free returned pointer
       */
      return QString::fromUtf8( libusb_strerror(code) );
    }

    /*! \brief Get an error string, that gan be displayed to the user
     *
     * \sa strerror()
     */
    static
    QString strerrorFromInt(int code) noexcept
    {
      return strerror( errorFromInt(code) );
    }
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_LIBUSB_ERROR_H
