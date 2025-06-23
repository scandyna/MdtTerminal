// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_CONTROL_TRANSFER_H
#define MDT_USB_CONTROL_TRANSFER_H

#include "Mdt/Usb/DeviceHandle.h"
#include "Mdt/Usb/ControlSetup.h"
#include "Mdt/Usb/LibusbRuntimeError.h"
#include "mdt_usb_export.h"
#include <chrono>

namespace Mdt{ namespace Usb{

  /*! \brief Perform a (synchronous) USB control transfer
   *
   * This is a helper around libusb_control_transfer()
   *
   * \return on success, the number of bytes actually transferred,
   * otherwise a libusb error.
   * The return value is the one returned by libusb_control_transfer()
   *
   * \sa https://libusb.sourceforge.io/api-1.0/group__libusb__syncio.html
   */
  MDT_USB_EXPORT
  int controlTransferNoexcept(DeviceHandle &deviceHandle, const ControlSetup & setup, unsigned char *data, std::chrono::milliseconds timeout) noexcept;

  /*! \brief Perform a (synchronous) USB control transfer
   *
   * This is a helper around controlTransferNoexcept().
   *
   * \exception LibusbRuntimeError
   */
  MDT_USB_EXPORT
  void controlTransfer(DeviceHandle &deviceHandle, const ControlSetup & setup, unsigned char *data, std::chrono::milliseconds timeout);

  /*! \brief Perform a (synchronous) USB control transfer
   *
   * This is a helper around controlTransferNoexcept() for requests
   * having no data exchange stage with the device.
   *
   * \pre the wLength field of \a setup must be 0
   * \sa controlTransferNoexcept()
   */
  MDT_USB_EXPORT
  int controlTransferWithoutDataNoexcept(DeviceHandle &deviceHandle, const ControlSetup & setup, std::chrono::milliseconds timeout) noexcept;

  /*! \brief Perform a (synchronous) USB control transfer
   *
   * This is a helper around controlTransferWithoutDataNoexcept().
   *
   * \pre the wLength field of \a setup must be 0
   * \exception LibusbRuntimeError
   */
  MDT_USB_EXPORT
  void controlTransferWithoutData(DeviceHandle &deviceHandle, const ControlSetup & setup, std::chrono::milliseconds timeout);

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_CONTROL_TRANSFER_H
