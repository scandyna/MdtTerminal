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

/**
 * https://docs.kernel.org/driver-api/tty/index.html
 * https://docs.kernel.org/driver-api/serial/driver.html
 * https://docs.kernel.org/driver-api/serial/serial-rs485.html
 * https://docs.kernel.org/usb/usb-serial.html
 */


}} // namespace Mdt{ namespace SerialPort{
