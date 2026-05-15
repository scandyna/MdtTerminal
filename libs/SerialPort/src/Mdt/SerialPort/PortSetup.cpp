// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortSetup.h"
#include "SettingsRawData.h"
#include "SettingsBuilder.h"
#include "Device/MoxaUPort.h"
#include <QSerialPortInfo>
#include <cassert>


namespace Mdt{ namespace SerialPort{

void PortSetup::setSettingsToPort(const Settings & settings, QSerialPort & port)
{
  assert( !port.isOpen() );

  port.setPortName( settings.portName() );
  port.setBaudRate( settings.baudRate() );
  port.setDataBits( settings.dataBits() );
  port.setParity( settings.parity() );
  port.setStopBits( settings.stopBits() );
  port.setFlowControl( settings.flowControl() );
}

Settings PortSetup::getSettingsFromPort(const QSerialPort & port)
{
  SettingsRawData data;

  QSerialPortInfo portInfo(port);

  data.portInfo = PortInfo::fromQSerialPortInfo(portInfo);
  data.baudRate = port.baudRate();
  data.dataBits = port.dataBits();
  data.parity = port.parity();
  data.stopBits = port.stopBits();
  data.flowControl = port.flowControl();

  return SettingsBuilder::settingsFromRawData(data);
}

bool PortSetup::hasVidAndPid(const PortInfo & portInfo) noexcept
{
  return portInfo.hasVendorIdentifier() && portInfo.hasProductIdentifier();
}

bool PortSetup::isMoxaUPort_1250_1450_1650(const PortInfo & portInfo) noexcept
{
  if( !hasVidAndPid(portInfo) ){
    return false;
  }
  if( !Device::vendorIdentifierIsMoxa( portInfo.vendorIdentifier() ) ){
    return false;
  }

  return Device::productIdentifierIsMoxaUPort_1250_1450_1650( portInfo.productIdentifier() );
}

UsbVendorIdProductId PortSetup::usbVendorIdProductIdFromPortInfo(const PortInfo & portInfo) noexcept
{
  assert( hasVidAndPid(portInfo) );

  return UsbVendorIdProductId{portInfo.vendorIdentifier(), portInfo.productIdentifier()};
}

}} // namespace Mdt{ namespace SerialPort{
