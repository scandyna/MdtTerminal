// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_CONTEXT_H
#define MDT_USB_CONTEXT_H

#include "Mdt/Usb/LibusbRuntimeError.h"
#include "mdt_usb_export.h"
#include <libusb.h>

namespace Mdt{ namespace Usb{

  /*! \brief A libusb context (or session)
   *
   * \sa https://libusb.sourceforge.io/api-1.0/group__libusb__lib.html
   */
  class MDT_USB_EXPORT Context
  {
   public:

    /*! \brief Construct a context
     *
     * \exception LibusbRuntimeError
     *
     * \todo Once 1.0.27 available, use libusb_init_context()
     *  (conan provides 1.0.26 in 2025).
     *  At this stage, add an optional list wrapping a list of libusb_init_option
     */
    Context();

    /*! \brief Deinit the context and free resources
     */
    ~Context() noexcept;

    Context(const Context &) = delete;
    Context & operator=(const Context &) = delete;

    Context(Context &&) = delete;
    Context & operator=(Context &&) = delete;

    /*! \brief Access the libusb context
     */
    libusb_context *libusbContext() const noexcept
    {
      return mContext;
    }

   private:

    libusb_context *mContext = nullptr;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_CONTEXT_H
