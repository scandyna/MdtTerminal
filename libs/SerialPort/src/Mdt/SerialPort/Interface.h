// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_INTERFACE_H
#define MDT_SERIAL_PORT_INTERFACE_H

#include "mdt_serialport_export.h"
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Attributes of an item in an interface list
   *
   * \sa InterfaceList
   */
  class MDT_SERIALPORT_EXPORT Interface
  {
   public:

    Interface() = delete;

    /*! \brief Get the name of this interface
     */
    QString name() const noexcept
    {
      return mName;
    }

    /*! \brief Get the parameter value for this interface
     */
    unsigned int parameterValue() const noexcept
    {
      return mParameterValue;
    }

    /*! \brief Build an interface from given name and parameter value
     */
    static
    Interface fromNameAndParameterValue(const QString & name, unsigned int value) noexcept;

   private:

    Interface(const QString & name, unsigned int value) noexcept;

    QString mName;
    unsigned int mParameterValue = 0;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_INTERFACE_H
