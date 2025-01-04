// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_RAW_DATA_H
#define MDT_SERIAL_PORT_SETTINGS_RAW_DATA_H

#include "mdt_serialport_export.h"
#include <QSerialPort>
#include <QtGlobal>

namespace Mdt{ namespace SerialPort{

  /*! \brief Serial port settings raw data
   *
   * This struct can be used in an editor.
   * To extract valid settings, SettingsBuilder can be used.
   *
   * \sa Settings
   * \sa SettingsBuilder
   * \sa SettingsValidation
   */
  struct MDT_SERIALPORT_EXPORT SettingsRawData
  {
    qint32 baudRate = 0;
    QSerialPort::DataBits dataBits = QSerialPort::UnknownDataBits;
    QSerialPort::Parity parity = QSerialPort::UnknownParity;
    QSerialPort::FlowControl flowControl = QSerialPort::UnknownFlowControl;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_RAW_DATA_H
