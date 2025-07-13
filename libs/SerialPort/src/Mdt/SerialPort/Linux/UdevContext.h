// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_LINUX_UDEV_CONTEXT_H
#define MDT_SERIAL_PORT_LINUX_UDEV_CONTEXT_H

#include "mdt_serialport_export.h"
#include <libudev.h>

namespace Mdt{ namespace SerialPort{ namespace Linux{

  /*! \brief Wrapper around a libudev context
   *
   * \sa https://man7.org/linux/man-pages/man3/libudev.3.html
   */
  class MDT_SERIALPORT_EXPORT UdevContext
  {
   public:

    /*! \brief Construct a context
     *
     * \exception std::bad_alloc
     */
    explicit
    UdevContext();

    /*! \brief Free the context
     */
    ~UdevContext() noexcept;

    UdevContext(const UdevContext &) = delete;
    UdevContext & operator=(const UdevContext &) = delete;

    UdevContext(UdevContext &&) = delete;
    UdevContext & operator=(UdevContext &&) = delete;

    /*! \brief Get the udev native context pointer
     */
    udev *nativePointer() const noexcept
    {
      return mContext;
    }

   private:

    udev *mContext;
  };

}}} // namespace Mdt{ namespace SerialPort{ namespace Linux{

#endif // #ifndef MDT_SERIAL_PORT_LINUX_UDEV_CONTEXT_H
