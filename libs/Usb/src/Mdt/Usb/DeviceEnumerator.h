// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_USB_DEVICE_ENUMERATOR_H
#define MDT_USB_DEVICE_ENUMERATOR_H

#include "Mdt/Usb/LibusbDeviceList.h"
#include "Mdt/Usb/Context.h"
#include "Mdt/Usb/LibusbRuntimeError.h"
#include "mdt_usb_export.h"
#include <QObject>
#include <memory>

namespace Mdt{ namespace Usb{

  /*! \brief USB device enumerator
   */
  class MDT_USB_EXPORT DeviceEnumerator : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Construct an enumerator for given context
     *
     * \pre \a context must be valid
     */
    DeviceEnumerator(std::shared_ptr<Context> context, QObject *parent = nullptr);

    /*! \brief Get a list of attached devices on the system
     *
     * \exception LibusbRuntimeError
     */
    LibusbDeviceList scanForAttachedDevices();

   private:

    std::shared_ptr<Context> mContext;
  };

}} // namespace Mdt{ namespace Usb{

#endif // #ifndef MDT_USB_DEVICE_ENUMERATOR_H
