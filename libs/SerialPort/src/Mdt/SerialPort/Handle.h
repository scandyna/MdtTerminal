// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_HANDLE_H
#define MDT_SERIAL_PORT_HANDLE_H

#include "mdt_serialport_export.h"
#include <QtGlobal>

namespace Mdt{ namespace SerialPort{

  /*! \brief Helper class to represent a native handle
   *
   * This class is used for platform specific implementations.
   */
  class MDT_SERIALPORT_EXPORT Handle
  {
#ifdef Q_OS_WIN32
    using NativeHandle = void*;
#else
    using NativeHandle = int;
#endif

   public:

    /*! \brief Check if this handle is null
     */
    bool isNull() const noexcept
    {
      return nativeHandleIsNull(mNativeHandle);
    }

    /*! \brief Get the native handle
     */
    NativeHandle nativeHandle() const noexcept
    {
      return mNativeHandle;
    }

    /*! \brief Get a handle from given native handle
     */
    static
    Handle fromNativeHandle(NativeHandle h);

    /*! \brief Check if given native handle is null
     */
    static
    bool nativeHandleIsNull(NativeHandle h) noexcept;

   private:

    Handle(NativeHandle h) noexcept
     : mNativeHandle(h)
    {
    }

    NativeHandle mNativeHandle;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_HANDLE_H
