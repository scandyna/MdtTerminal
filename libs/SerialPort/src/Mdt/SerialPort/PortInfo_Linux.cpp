// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortInfo.h"
#include <QString>
#include <QLatin1String>
#include <QByteArray>
#include <fcntl.h>        // open()
#include <unistd.h>       // close()
#include <sys/ioctl.h>
#include <linux/serial.h> // serial_struct
#include <cassert>

namespace Mdt{ namespace SerialPort{

bool isExisting_ttyS_port(const QString & systemLocation)
{
  const mode_t flags = O_RDWR | O_NONBLOCK | O_NOCTTY;
  const int fd = ::open(systemLocation.toLocal8Bit().constData(), flags);
  if(fd < 0){
    return false;
  }

  serial_struct serinfo;
  const int retval = ::ioctl(fd, TIOCGSERIAL, &serinfo);
  ::close(fd);
  if(retval < 0){
    return false;
  }

  return serinfo.type != PORT_UNKNOWN;
}

bool isExistingSerialPort(const PortInfo & portInfo)
{
  if( portInfo.portName().startsWith( QLatin1String("ttyS") ) ){
    return isExisting_ttyS_port( portInfo.systemLocation() );
  }
  return true;
}

}} // namespace Mdt{ namespace SerialPort{
