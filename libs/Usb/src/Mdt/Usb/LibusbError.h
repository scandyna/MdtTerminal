// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_LIBUSB_ERROR_H
#define MDT_USB_LIBUSB_ERROR_H

#include "mdt_usb_export.h"
#include <QString>
#include <libusb.h>
#include <cassert>

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
     *
     * \pre \a code must be <= 0
     */
    static
    libusb_error errorFromInt(int code) noexcept
    {
      assert(code <= 0);

      return static_cast<libusb_error>(code);
    }

    /*! \brief Get a libusb_error from given code
     *
     * \pre \a code must be <= 0
     */
    static
    libusb_error errorFrom_ssize_t(ssize_t code) noexcept
    {
      assert(code <= 0);
      /*
       * We should trust that libusb functions returns correct code,
       * that fits libusb_error enum, as long its <=0 (LIBUSB_SUCCESS is 0).
       */
      return static_cast<libusb_error>(code);
    }

    /*! \brief Get a QString representation of given code
     *
     * \pre \a code must be <= 0
     */
    static
    QString errorName(libusb_error code) noexcept;

    /*! \brief Get a QString representation of given code
     *
     * \pre \a code must be <= 0
     */
    static
    QString errorNameFromInt(int code) noexcept
    {
      assert(code <= 0);

      return errorName( errorFromInt(code) );
    }

    /*! \brief Get a QString representation of given code
     *
     * \pre \a code must be <= 0
     */
    static
    QString errorNameFrom_ssize_t(ssize_t code) noexcept
    {
      assert(code <= 0);

      return errorName( errorFrom_ssize_t(code) );
    }

    /*! \brief Get an error string, that gan be displayed to the user
     */
    static
    QString strerror(libusb_error code) noexcept
    {
      /*
       * libusb_strerror() returns UTF-8
       * We must not free returned pointer
       */
      return QString::fromUtf8( libusb_strerror(code) );
    }

    /*! \brief Get an error string, that gan be displayed to the user
     *
     * \pre \a code must be <= 0
     * \sa strerror()
     */
    static
    QString strerrorFromInt(int code) noexcept
    {
      assert(code <= 0);

      return strerror( errorFromInt(code) );
    }

    /*! \brief Get an error string, that gan be displayed to the user
     *
     * \pre \a code must be <= 0
     * \sa strerror()
     */
    static
    QString strerrorFrom_ssize_t(ssize_t code) noexcept
    {
      assert(code <= 0);

      return strerror( errorFrom_ssize_t(code) );
    }

  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_LIBUSB_ERROR_H
