// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "UdevContext.h"
#include <new>

namespace Mdt{ namespace SerialPort{ namespace Linux{

UdevContext::UdevContext()
 : mContext( udev_new() )
{
  if(mContext == nullptr){
    throw std::bad_alloc();
  }
}

UdevContext::~UdevContext() noexcept
{
  udev_unref(mContext);
}

}}} // namespace Mdt{ namespace SerialPort{ namespace Linux{
