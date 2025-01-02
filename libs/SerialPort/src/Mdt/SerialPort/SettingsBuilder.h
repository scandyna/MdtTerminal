// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_BUILDER_H
#define MDT_SERIAL_PORT_SETTINGS_BUILDER_H

#include "Mdt/SerialPort/Settings.h"
#include "Mdt/SerialPort/SettingsRawData.h"
#include "mdt_serialport_export.h"
#include <QObject>

namespace Mdt{ namespace SerialPort{

  /*! \brief Settings builder
   *
   * \sa Settings
   * \sa SettingsRawData
   * \sa SettingsValidation
   */
  class MDT_SERIALPORT_EXPORT SettingsBuilder : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Get settings from given raw data
     *
     * \exception SettingsValidationError
     */
    static
    Settings settingsFromRawData(const SettingsRawData & data);
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_BUILDER_H
