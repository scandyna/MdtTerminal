// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Engine.h"

#include <QString>

#include <errno.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#include <string.h> // memset()

#include <QDebug>

namespace Mdt{ namespace SerialPort{

// UnixEngine::UnixEngine(int descriptor)
//  : mDescriptor(descriptor)
// {
//   /// \todo pre
// }

/**
 * https://docs.kernel.org/driver-api/tty/index.html
 * https://docs.kernel.org/driver-api/serial/driver.html
 * https://docs.kernel.org/driver-api/serial/serial-rs485.html
 * https://docs.kernel.org/usb/usb-serial.html
 */

/*
 * Some notes about some Moxa Uport devices.
 *
 * On Linux, the official Linux driver, mxuport,
 * does not implement the TIOCGSERIAL and TIOCSSERIAL ioctl's.
 *
 * The Linux drivers provided by Moxa implement those.
 *
 * Query the device about current interface seems not possible.
 * Looking around the official Linux driver, mxuport.c,
 * and also the Moxa provided one, I could not find how to get this interface.
 *
 * The Moxa driver sets the interface in mx_init_port() (with an USB control call),
 * called by mxuport_open(), to the requested interface.
 * in mxuport_port_probe(), the interface is defined to RS-232.
 *
 * The official Linux driver sets the RS-232 interface in mxuport_port_probe()
 * (with an USB control call).
 */

// void UnixEngine::configureInterface(const Interface & interface)
// {
//   qDebug() << "configureInterface() - mDescriptor: " << mDescriptor;
// 
//   sandbox();
// 
//   return;
// 
//   struct serial_struct serial;
//   ::memset( &serial, 0, sizeof(serial) );
// 
//   int result = ::ioctl(mDescriptor, TIOCGSERIAL, &serial);
//   if(result == -1){
//     const QString msg = QString::fromLocal8Bit( ::strerror(errno) );
//     qDebug() << " error " << errno << " : " << msg;
//   }
// 
//   qDebug() << " port num: " << serial.port;
//   
//   serial.port = interface.parameterValue();
//   
//   /// \todo if already the same, done here
//   
//   result = ::ioctl(mDescriptor, TIOCSSERIAL, &serial);
//   if(result == -1){
//     const QString msg = QString::fromLocal8Bit( ::strerror(errno) );
//     qDebug() << " error " << errno << " : " << msg;
//   }
// 
// }

// void UnixEngine::sandbox()
// {
//   struct serial_rs485 rs485conf;
//   ::memset( &rs485conf, 0, sizeof(serial_rs485) );
// 
//   int result = ::ioctl(mDescriptor, TIOCGRS485, &rs485conf);
//   if(result == -1){
//     const QString msg = QString::fromLocal8Bit( ::strerror(errno) );
//     qDebug() << " error " << errno << " : " << msg;
//   }
// 
// }

}} // namespace Mdt{ namespace SerialPort{
