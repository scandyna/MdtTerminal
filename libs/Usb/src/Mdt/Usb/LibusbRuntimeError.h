// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_LIBUSB_RUNTIME_ERROR_H
#define MDT_USB_LIBUSB_RUNTIME_ERROR_H

#include "Mdt/Usb/QRuntimeError.h"
#include "mdt_usb_export.h"
#include <QString>
#include <libusb.h>

namespace Mdt{ namespace Usb{

  /*! \brief Exception based on libusb_error
   *
   * \sa LibusbError
   */
  class MDT_USB_EXPORT LibusbRuntimeError : public QRuntimeError
  {
   public:

    /*! \brief Constructor
     */
    explicit
    LibusbRuntimeError(const QString & text, libusb_error code) noexcept
     : QRuntimeError(text),
       mErrorCode(code)
    {
    }

    /*! \brief Copy construct an error from \a other
     */
    LibusbRuntimeError(const LibusbRuntimeError & other) noexcept = default;

    /*! \brief Copy assign \a other to this error
     */
    LibusbRuntimeError & operator=(const LibusbRuntimeError & other) noexcept = default;

    /*! \brief Get the libusb error code
     */
    libusb_error errorCode() const noexcept
    {
      return mErrorCode;
    }

   private:

    libusb_error mErrorCode;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_LIBUSB_RUNTIME_ERROR_H
