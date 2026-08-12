// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_INTERFACE_H
#define MDT_SERIAL_PORT_INTERFACE_H

#include "Mdt/SerialPort/InterfaceStandard.h"
#include "mdt_serialport_export.h"
#include <cstdint>

namespace Mdt{ namespace SerialPort{

  /*! \brief Attributes of an item in an interface list
   *
   * \sa InterfaceList
   */
  class MDT_SERIALPORT_EXPORT Interface
  {
   public:

    /*! \brief Construct a default interface
     *
     * A default interface is RS-232
     * and can't be configured.
     */
    Interface() noexcept = default;

    /*! \brief Get the standard of this interface
     */
    InterfaceStandard standard() const noexcept
    {
      return mStandard;
    }

    /*! \brief Check if the interface is configurable on the device
     */
    bool isConfigurable() const noexcept
    {
      return mIsConfigurable;
    }

    /*! \brief Get the parameter value for this interface
     */
    uint16_t parameterValue() const noexcept
    {
      return mParameterValue;
    }

    /*! \brief Build an interface from given name and parameter value
     */
    static
    Interface fromStandardAndParameterValue(InterfaceStandard standard, uint16_t value) noexcept;

    /*! \brief Returns an interface handled by the system
     *
     * \sa InterfaceList
     */
    static
    Interface systemHandledOnly();

   private:

    Interface(InterfaceStandard standard, uint16_t value, bool isConfigurable) noexcept;

    InterfaceStandard mStandard = InterfaceStandard::RS_232;
    uint16_t mParameterValue = 0;
    bool mIsConfigurable = false;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_INTERFACE_H
