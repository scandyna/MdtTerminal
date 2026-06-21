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
#include <QtEnvironmentVariables>
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

QString serialPortNameWithBridgePlug()
{
  constexpr const char* envVarName = "MDT_SERIALPORT_TEST_PORT_NAME_WITH_BRIDGE_PLUG";

  QString portName = qEnvironmentVariable(envVarName);
  if( portName.isEmpty() ){
    qDebug() << "A test called Mdt::SerialPort::TestLib::serialPortNameWithBridgePlug() "
                "because it requires to open as serial port with a bridge plug.\n"
                "To work, the " << envVarName << " environment variable has to be set.\n"
                "Please set this variable with the port name having the bridge plug attached.\n"
                "The port name should be like ttyS0 on Unix, or COM1 on Windows";
  }

  return portName;
}

std::optional<PortInfo> findSerialPortWithBridgePlug()
{
  const QString portName = serialPortNameWithBridgePlug();
  if( portName.isEmpty() ){
    return {};
  }

  const auto availablePorts = QSerialPortInfo::availablePorts();
  for(const auto & qPortInfo : availablePorts){
    if(qPortInfo.portName() == portName){
      auto portInfo = PortInfo::fromQSerialPortInfo(qPortInfo);
      if( isExistingSerialPort(portInfo) ){
        return portInfo;
      }
    }
  }

  qDebug() << "could not find a serial port named " << portName;
  return {};
}

bool openSerialPortWithBridgePlug(QSerialPort & serialPort)
{
  assert( !serialPort.isOpen() );

  const QString portName = serialPortNameWithBridgePlug();
  if( portName.isEmpty() ){
    return false;
  }

  serialPort.setPortName(portName);
  if( !serialPort.open(QSerialPort::ReadWrite) ){
    qDebug() << "open serial port " << serialPort.portName() <<  " failed: " << serialPort.errorString();
    return false;
  }

  return true;
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
