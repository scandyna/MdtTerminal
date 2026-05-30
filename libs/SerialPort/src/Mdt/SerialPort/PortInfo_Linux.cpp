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
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/serial.h> // serial_struct
#include <cassert>

namespace Mdt{ namespace SerialPort{

/*! \internal Helper around POSIX open()
 *
 * This variant handles the EINTR error,
 * and avoids a lifetime bug.
 *
 * See also Qt source code
 * qtbase/src/corelib/kernel/qcore_unix_p.h
 *
 * \note No close() wrapper is provided today.
 * It is NOT recommended to loop to filter out EINTR.
 * It is safer to just call close() once.
 *
 * \todo Should go to some appropriate place
 */
int mdt_posix_open(const QString & path, int flags, mode_t mode = 0777)
{
  int fd;
  const QByteArray baPath = path.toLocal8Bit();

  do{
    fd = ::open(baPath.constData(), flags, mode);
  }while(fd == -1 && errno == EINTR);

  return fd;
}

bool isExisting_ttyS_port(const QString & systemLocation)
{
  const mode_t flags = O_RDWR | O_NONBLOCK | O_NOCTTY;
  const int fd = mdt_posix_open(systemLocation, flags);
  // const int fd = ::open(systemLocation.toLocal8Bit().constData(), flags);
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
