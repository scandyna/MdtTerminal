// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
/// \todo Sandbox includes

/*
 * Some macros to define before including windows.h
 * NOTE: do not include anything before here
 */

// Disable min and max to prevent conflict with std::min/max
#ifndef NOMINMAX
  #define NOMINMAX
#endif

// Disable including old/deprecated or rarely used heavy stuff
#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winioctl.h>

#include "Mdt/SerialPort/PortSetup.h"
#include "catch2/catch.hpp"
#include "Catch2QString.h"


#include "Mdt/SerialPort/Device/MoxaUPort.h"
#include "Mdt/SerialPort/InterfaceStringFormat.h"
#include <Mdt/Numeric/Limits.h>
#include <Mdt/Numeric/BasicConversion.h>
#include <QString>
#include <QByteArray>
#include <QSerialPort>
#include <string>

#include <QDebug>

#include <system_error>
#include <cassert>

using namespace Mdt::SerialPort;

/// \todo Sandbox

using DWORD = unsigned long;  // TODO: remove 

QString tr(const char *s)
{
  return QString(s);
}

/// \todo Put to some common Windows specific location
QString systemErrorMessageFromWin32Code(DWORD errorCode)
{
  using Mdt::Numeric::int_canHoldValueOf_T;
  using Mdt::Numeric::int_from_T;

  assert( int_canHoldValueOf_T(errorCode) );

  std::string str = std::system_category().message( int_from_T(errorCode) );
  auto ba = QByteArray::fromStdString(str);

  return QString::fromLocal8Bit(ba).trimmed();
}

// Code IOCTL propriétaire de Moxa pour définir le mode de fonctionnement (Interface)
#define IOCTL_MOXA_SET_INTERFACE    CTL_CODE(FILE_DEVICE_SERIAL_PORT, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
// Code IOCTL propriétaire de Moxa pour LIRE le mode/interface
#define IOCTL_MOXA_GET_INTERFACE    CTL_CODE(FILE_DEVICE_SERIAL_PORT, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)

void sandboxSetInterface(const Interface & interface, QSerialPort & port)
{
  assert( port.isOpen() );
  assert( port.isReadable() );
  assert( port.isWritable() );

  HANDLE hComm = port.handle();
  assert(hComm != INVALID_HANDLE_VALUE);

  DWORD portInterface = interface.parameterValue();
    // 2. Traduction de votre énumération/valeur vers le format attendu par Moxa
    // Remplacez par votre logique (ex: interface.parameterValue()) 
    // DWORD portMode = MOXA_RS232; 
    // if (interface.isRS485_2W()) portMode = MOXA_RS485_2W;
    // else if (interface.isRS422()) portMode = MOXA_RS422;
    // else if (interface.isRS485_4W()) portMode = MOXA_RS485_4W;

  DWORD bytesReturned = 0;
  BOOL success = ::DeviceIoControl(
    hComm,                    // Handle to the COM port
    IOCTL_MOXA_SET_INTERFACE, // Moxa IOCTL Code
    &portInterface,           // Input buffer (here, port interface)
    sizeof(portInterface),    // Input buffer size
    nullptr,                  // No output buffer
    0,                        // Output buffer size
    &bytesReturned,           // Bytes returned in output buffer - Always required
    nullptr                   // No asynchronous I/O (Overlapped)
  );

  if(!success){
    DWORD errorCode = ::GetLastError();
    QString msg = tr("configure interface failed by calling DeviceIoControl(). Windows error code: %1 - text: %2")
                  .arg(errorCode)
                  .arg( systemErrorMessageFromWin32Code(errorCode) );
    throw PortSetupError(msg);
  }
}

Interface sandboxGetInterface(QSerialPort & port)
{
  assert( port.isOpen() );
  assert( port.isReadable() );
  assert( port.isWritable() ); /// required ?

  HANDLE hComm = port.handle();
  assert(hComm != INVALID_HANDLE_VALUE);

  // 1. Récupération du Handle Windows depuis Qt
    // HANDLE hComm = reinterpret_cast<HANDLE>(port.handle());
    // if (hComm == INVALID_HANDLE_VALUE) {
    //     throw PortSetupError(tr("Erreur : Handle Windows invalide."));
    // }

  DWORD portInterface = 0; 
  DWORD bytesReturned = 0;

    // 3. Appel de DeviceIoControl avec le code IOCTL de lecture
    // BOOL success = ::DeviceIoControl(
    //     hComm,                        // Handle du port ouvert
    //     IOCTL_MOXA_GET_INTERFACE,     // Code de LECTURE
    //     NULL,                         // Aucun buffer d'entrée requis
    //     0,                            // Taille entrée = 0
    //     &currentInterface,                 // Buffer de sortie pour recevoir la valeur
    //     sizeof(currentInterface),          // Taille du buffer de sortie (4 octets)
    //     &bytesReturned,               // Nombre d'octets réellement écrits
    //     NULL                          // Mode synchrone
    // );

  BOOL success = ::DeviceIoControl(
    hComm,                    // Handle to the COM port
    IOCTL_MOXA_GET_INTERFACE, // Moxa IOCTL Code
    nullptr,                  // No input buffer
    0,                        // Input buffer size
    &portInterface,           // Output buffer (here, port interface)
    sizeof(portInterface),    // Output buffer size
    &bytesReturned,           // Bytes returned in output buffer
    nullptr                   // No asynchronous I/O (Overlapped)
  );

  if(!success){
    DWORD errorCode = ::GetLastError();
    QString msg = tr("getting interface failed by calling DeviceIoControl(). Windows error code: %1 - text: %2")
                  .arg(errorCode)
                  .arg( systemErrorMessageFromWin32Code(errorCode) );
    throw PortSetupError(msg);
  }
    // 4. Gestion d'erreur Windows
    // if (!success) {
    //     DWORD errorCode = ::GetLastError();
    //     throw PortSetupError(tr("Impossible de lire l'interface Moxa. Code d'erreur Win32 : %1").arg(errorCode));
    // }

  if( bytesReturned != sizeof(portInterface) ){
    QString msg = tr("getting interface failed: mismatch between output buffer size and returned bytes count DeviceIoControl()");
    throw PortSetupError(msg);
  }

  if(portInterface > 3){
    QString msg = tr("getting interface failed: returned parameter value %1 is not valid")
                  .arg(portInterface);
    throw PortSetupError(msg);
  }
  const uint16_t parameterValue = static_cast<uint16_t>(portInterface);

  return Interface::fromStandardAndParameterValue(Device::interfaceStandardFromMoxaUport_1250_1450_1650_ParameterValue(parameterValue), parameterValue);
}

TEST_CASE("sandbox")
{
  const QString portName = "COM1";
  const auto rs422Interface = Interface::fromStandardAndParameterValue(InterfaceStandard::RS_422, 0x2);
  QSerialPort serialPort;

  serialPort.setPortName(portName);
  if( !serialPort.open(QSerialPort::ReadWrite) ){
    qDebug() << "open serial port " << serialPort.portName() <<  " failed: " << serialPort.errorString();
    FAIL();
  }

  sandboxSetInterface(rs422Interface, serialPort);

  const auto interface = sandboxGetInterface(serialPort);
  qDebug() << "Port interface: " << interface.parameterValue() << " - " << InterfaceStringFormat::standardName( interface.standard() );
}
