// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_ABSTRACT_ENGINE_H
#define MDT_SERIAL_PORT_ABSTRACT_ENGINE_H

// #include "Mdt/SerialPort/Handle.h"

// #include "Mdt/SerialPort/Interface.h"
#include "mdt_serialport_export.h"

namespace Mdt{ namespace SerialPort{

  /*! \brief Interface to implement platform specifics
   */
  class MDT_SERIALPORT_EXPORT AbstractEngine
  {
   public:

    /*! \brief Construct an engine
     *
     * \pre \a handle must refere to an open port
     * (i.e. handle must not be null)
     *
     * \warning The handle must stay valid for the whole lifetime of this engine
     */
    // explicit
    // AbstractEngine(Handle handle);

    // virtual
    // void configureInterface(const Interface & interface) = 0;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ABSTRACT_ENGINE_H
