// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SettingsValidation.h"
#include "ParityStringFormat.h"
#include "FlowControlStringFormat.h"
#include "StopBitsStringFormat.h"
#include "Settings.h"
#include "SendByteByByteSettings.h"
#include <QString>

namespace Mdt{ namespace SerialPort{

void SettingsValidation::validateSettings(const SettingsRawData & data)
{
  validatePortName(data.portName);
  validateBaudRate(data.baudRate);
  validateDataBits(data.dataBits);
  validateParity(data.parity);
  validateFlowControl(data.flowControl);
  validateStopBits(data.stopBits);
  validateSendByteByByteSettings(data.sendByteByByteIsEnabled, data.sendByteByByteIntervalInMilliseconds);
}

void SettingsValidation::validatePortName(const QString & name)
{
  if( !Settings::portNameHasMinimalValidity(name) ){
    const QString msg = tr("Port name '%1' is not valid")
                        .arg(name);
    throw SettingsValidationError(msg);
  }
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

void SettingsValidation::validateParity(QSerialPort::Parity parity)
{
  if( !Settings::parityHasMinimalValidity(parity) ){
    QString msg = tr("parity %1 is not valid")
                  .arg( ParityStringFormat::parityToString(parity) );
    throw SettingsValidationError(msg);
  }
}

void SettingsValidation::validateFlowControl(QSerialPort::FlowControl control)
{
  if( !Settings::flowControlHasMinimalValidity(control) ){
    QString msg = tr("flow control %1 is not valid")
                  .arg( FlowControlStringFormat::flowControlToString(control) );
    throw SettingsValidationError(msg);
  }
}

void SettingsValidation::validateStopBits(QSerialPort::StopBits bits)
{
  if( !Settings::stopBitsHasMinimalValidity(bits) ){
    QString msg = tr("stop bits %1 is not valid")
                  .arg( StopBitsStringFormat::stopBitsToString(bits) );
    throw SettingsValidationError(msg);
  }
}

void SettingsValidation::validateSendByteByByteSettings(bool enable, int intervalInMilliseconds)
{
  if( !enable ){
    return;
  }
  if( !SendByteByByteSettings::rawIntervalInMillisecondsIsValid(intervalInMilliseconds) ){
    QString msg = tr("interval %1 ms is not valid to send byte by byte")
                  .arg(intervalInMilliseconds);
    throw SettingsValidationError(msg);
  }
}

}} // namespace Mdt{ namespace SerialPort{
