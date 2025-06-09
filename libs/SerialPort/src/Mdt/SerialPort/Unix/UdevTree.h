// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_UNIX_UDEV_TREE_H
#define MDT_SERIAL_PORT_UNIX_UDEV_TREE_H

#include "Mdt/SerialPort/Unix/UdevDevice.h"
#include "mdt_serialport_export.h"
#include <libudev.h>

namespace Mdt{ namespace SerialPort{ namespace Unix{

  /*! \brief Walk an Udev tree branch direction to root
   *
   * Calls the UnaryFunc \a f for each device node
   * during the walk, including the given start node \a device ,
   * until \a pred returns true.
   *
   * \note \a f is called before \a pred .
   *
   * UnaryFunc should be of the for:
   * \code
   * void f(udev_device *device);
   * \endcode
   *
   * UnaryPred should be of the form:
   * \code
   * bool p(udev_device *device);
   * \endcode
   *
   * The given device pointer will never be null
   * while calling \a p of \a f .
   */
  template<typename UnaryFunc, typename UnaryPred>
  void walkUdevTreeToRootUntil(const UdevDevice & device, UnaryFunc f, UnaryPred p)
  {
    udev_device *devicePtr = device.nativePointer();
    if(devicePtr == nullptr){
      return;
    }

    f(devicePtr);
    if( p(devicePtr) ){
      return;
    }

    for( udev_device *parent = udev_device_get_parent(devicePtr) ; parent != nullptr ; parent = udev_device_get_parent(parent) ){
      f(parent);
      if( p(parent) ){
        return;
      }
    }
  }

  /*! \brief Walk an Udev tree branch direction to root
   *
   * Calls the UnaryFunc \a f for each device node
   * during the walk, including the given start node \a device .
   *
   * UnaryFunc should be of the for:
   * \code
   * void f(udev_device *device);
   * \endcode
   *
   * The given device pointer will never be null.
   */
  template<typename UnaryFunc>
  void walkUdevTreeToRoot(const UdevDevice & device, UnaryFunc f)
  {
    const auto pred = [](udev_device *){
      return false;
    };

    walkUdevTreeToRootUntil(device, f, pred);
  }

}}} // namespace Mdt{ namespace SerialPort{ namespace Unix{

#endif // #ifndef MDT_SERIAL_PORT_UNIX_UDEV_TREE_H
