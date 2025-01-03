// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsValidation.h"
#include "Settings.h"
#include <QString>

namespace Mdt{ namespace SerialPort{

void SettingsValidation::validateSettings(const SettingsRawData & data)
{
  validateBaudRate(data.baudRate);
  validateDataBits(data.dataBits);
}

void SettingsValidation::validateBaudRate(qint32 rate)
{
  if( !Settings::baudRateHasMinimalValidity(rate) ){
    const QString msg = tr("Baud rate %1 is not valid")
                        .arg(rate);
    throw SettingsValidationError(msg);
  }
}

void SettingsValidation::validateDataBits(QSerialPort::DataBits bits)
{
  if( !Settings::dataBitsHasMinimalValidity(bits) ){
    const int bitsValue = static_cast<int>(bits);
    const QString msg = tr("Data bits %1 is not valid")
                        .arg(bitsValue);
    throw SettingsValidationError(msg);
  }
}

}} // namespace Mdt{ namespace SerialPort{