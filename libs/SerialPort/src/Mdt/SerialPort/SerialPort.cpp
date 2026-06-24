// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "SerialPort.h"
#include "PortSetup.h"
#include "Platform.h"
#include "PinoutSignalsEventNotifier.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

SerialPort::SerialPort(QObject *parent)
 : QObject(parent),
   mWriter(&mPort),
   mSettings( Settings::defaultSettings() )
{
  connect(&mPort, &QSerialPort::aboutToClose, this, &SerialPort::aboutToClose);
  connect(&mPort, &QSerialPort::errorOccurred, this, &SerialPort::errorOccurred);
  connect(&mPort, &QSerialPort::bytesWritten, this, &SerialPort::bytesWritten);
  connect(&mPort, &QSerialPort::readyRead, this, &SerialPort::readyRead);
}

/// \todo make default if nothing required here
SerialPort::~SerialPort() noexcept
{
}

void SerialPort::setPinoutSignalsEventNotifierEnabled(bool enable)
{
  assert( !isOpen() );

  if(enable){
    if(mPinoutSignalsEventNotifier == nullptr){
      mPinoutSignalsEventNotifier = std::make_unique<PinoutSignalsEventNotifier>(&mPort);
      connect(mPinoutSignalsEventNotifier.get(), &PinoutSignalsEventNotifier::signalsChanged, this, &SerialPort::pinoutSignalsChanged);
    }
    assert(mPinoutSignalsEventNotifier != nullptr);
  }else{
    if(mPinoutSignalsEventNotifier != nullptr){
      mPinoutSignalsEventNotifier.reset();
    }
    assert(mPinoutSignalsEventNotifier == nullptr);
  }
}

void SerialPort::setSettings(const Settings & settings)
{
  assert( !isOpen() );

  mSettings = settings;
  mWriter.setSettings( settings.sendByteByByteSettings() );
}

void SerialPort::open(QIODeviceBase::OpenMode mode)
{
  assert( !isOpen() );
  assert( hasRequiredSettings() );

  PortSetup ps;

  try{
    ps.fetchPortInformations( mSettings.portInfo() );
  }catch(const FileOpenError & foError){
    QString text = tr("Error while initializing port setup: %1")
                   .arg( foError.text() );
    PortOpenError error(text);
    error.setInformativeText( foError.informativeText() );
    error.setDetailedText( foError.detailedText() );
    throw error;
  }

  try{
    ps.configureInterfaceBeforeOpenPortIfRequired( mSettings.interface() );
  }catch(const PortSetupError & psError){
    QString text = tr("Error while configuring interface for port %1 (before open)")
                   .arg( mSettings.portName() );
    PortOpenError error(text);
    error.setInformativeText( psError.informativeText() );
    error.setDetailedText( psError.detailedText() );
    throw error;
  }

  ps.setSettingsToPort(mSettings, mPort);
  /// mPort.setReadBufferSize(10);

  if( !mPort.open(mode) ){
    if(mPort.error() == QSerialPort::PermissionError){
      throwPermissionPortOpenError();
    }else{
      QString text = tr("Error while open serial port %1. System reported: %2")
                     .arg( mPort.portName(), mPort.errorString() );
      throw PortOpenError(text);
    }
  }

  try{
    ps.configureInterfaceOncePortOpenIfRequired(mSettings.interface(), mPort);
  }catch(const PortSetupError & psError){
    mPort.close();
    PortOpenError error( psError.text() );
    error.setInformativeText( psError.informativeText() );
    error.setDetailedText( psError.detailedText() );
    throw error;
  }

  if(mPinoutSignalsEventNotifier != nullptr){
    mPinoutSignalsEventNotifier->setPortOpen();
  }
}

void SerialPort::openReadOnly()
{
  assert( !isOpen() );
  assert( hasRequiredSettings() );

  open(QSerialPort::ReadOnly);
}

void SerialPort::openWriteOnly()
{
  assert( !isOpen() );
  assert( hasRequiredSettings() );

  open(QSerialPort::WriteOnly);
}

void SerialPort::openReadWrite()
{
  assert( !isOpen() );
  assert( hasRequiredSettings() );

  open(QSerialPort::ReadWrite);
}

void SerialPort::close()
{
  if( !mPort.isOpen() ){
    return;
  }

  /*
   * Some drivers/devices, like Moxa UPort Linux,
   * do not cancel break.
   */
  if(mPort.error() == QSerialPort::NoError){
    mPort.setBreakEnabled(false);
  }

  mPort.close();
}

qint64 SerialPort::write(const QByteArray &data)
{
  return mWriter.write(data);
}

QByteArray SerialPort::readAll()
{
  return mPort.readAll();
}

bool SerialPort::setDataTerminalReady(bool set)
{
  assert( isOpen() );

  return mPort.setDataTerminalReady(set);
}

bool SerialPort::setRequestToSend(bool set)
{
  assert( isOpen() );

  return mPort.setRequestToSend(set);
}

bool SerialPort::setBreakEnabled(bool set)
{
  assert( isOpen() );

  return mPort.setBreakEnabled(set);
}

void SerialPort::throwPermissionPortOpenError()
{
  QString text = tr(
    "Open serial port %1 failed due to permission error."
  ).arg( mPort.portName() );
  PortOpenError error(text);

  QString informativeText = tr(
    "The device may already be locked by another program, or you don't have the permissions to open it.\n"
    "System reported: %1"
  ).arg( mPort.errorString() );
  error.setInformativeText(informativeText);

  if constexpr( osIsLinux() ){
    QString linuxDetailedText = tr(
      "On Linux, like Ubuntu, you may not be in the dialout group. Maybe try:\n"
      "sudo adduser <user> dialout\n"
      "Then logoff and login again (your groups can be listed with the groups command)."
    );
    error.setDetailedText(linuxDetailedText);
  }

  throw error;
}

}} // namespace Mdt{ namespace SerialPort{
