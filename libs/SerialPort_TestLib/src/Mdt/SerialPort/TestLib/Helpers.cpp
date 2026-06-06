// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Helpers.h"
#include <QDebug>
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace TestLib{

std::optional<PortInfo> findFirstAvailableSerialPort()
{
  const auto availablePorts = QSerialPortInfo::availablePorts();
  for(const auto & qPortInfo : availablePorts){
    auto portInfo = PortInfo::fromQSerialPortInfo(qPortInfo);
    if( isExistingSerialPort(portInfo) ){
      return portInfo;
    }
  }

  qDebug() << "could not find any serial port";
  return {};
}

bool openSerialPort(QSerialPort & serialPort, QSerialPort::OpenMode openMode, const Mdt::SerialPort::PortInfo & portInfo)
{
  assert( !serialPort.isOpen() );

  serialPort.setPortName( portInfo.portName() );
  if( !serialPort.open(openMode) ){
    qDebug() << "open serial port " << serialPort.portName() <<  " failed: " << serialPort.errorString();
    return false;
  }

  return true;
}

bool openFirstAvailableSerialPort(QSerialPort & serialPort, QSerialPort::OpenMode openMode)
{
  assert( !serialPort.isOpen() );

  const auto portInfo = findFirstAvailableSerialPort();
  if( !portInfo.has_value() ){
    return false;
  }

  return openSerialPort(serialPort, openMode, *portInfo);
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
