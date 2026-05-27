// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_ENGINE_H
#define MDT_SERIAL_PORT_ENGINE_H

#include "Mdt/SerialPort/Handle.h"

#include "Mdt/SerialPort/PortInfo.h"

#include "mdt_serialport_export.h"

namespace Mdt{ namespace SerialPort{

  /*! \brief 
   *
   * \todo maybe not useful 
   */
  class MDT_SERIALPORT_EXPORT Engine
  {
   public:

    /*! \brief Open XXXX
     *
     * \todo here, maybe do not depend on PortInfo 
     *
     * \exception 
     *
     * \pre 
     */
    Handle openPortReadOnly_XXXX_(const PortInfo & portInfo);

    /*! \brief
     *
     * \pre 
     */
    void closePort(Handle handle);
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ENGINE_H
