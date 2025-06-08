// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_UNIX_ENGINE_H
#define MDT_SERIAL_PORT_UNIX_ENGINE_H

#include "Mdt/SerialPort/AbstractEngine.h"
#include "mdt_serialport_export.h"

namespace Mdt{ namespace SerialPort{

  /*! \brief Unix specific implementations
   *
   * \todo Linux specific - Should be LinuxEngine
   */
  class MDT_SERIALPORT_EXPORT UnixEngine : public AbstractEngine
  {
   public:

    explicit
    UnixEngine(int descriptor);

  // private:

    void configureInterface(const Interface & interface) override;

   private:

    void sandbox();

    int mDescriptor;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_UNIX_ENGINE_H
