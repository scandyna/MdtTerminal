// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_RAW_DATA_H
#define MDT_SERIAL_PORT_SETTINGS_RAW_DATA_H

#include "Mdt/SerialPort/PortInfo.h"
#include "Mdt/SerialPort/Interface.h"
#include "mdt_serialport_export.h"
#include <QSerialPort>
#include <QtGlobal>
#include <QString>

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
    PortInfo portInfo;
    qint32 baudRate = 0;
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    Interface interface;
    bool sendByteByByteIsEnabled = false;
    int sendByteByByteIntervalInMilliseconds = 0;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_RAW_DATA_H
