// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtUsb
 ** Library to communicate with USB devices from user space.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "ControlTransfer.h"
#include "LibusbError.h"
#include "NumericLimits.h"
#include <QCoreApplication>
#include <QString>
#include <libusb.h>
#include <cassert>

namespace Mdt{ namespace Usb{

QString controlTransferTr(const char *sourceText) noexcept
{
  return QCoreApplication::translate("Mdt::Usb", sourceText);
}


int controlTransferNoexcept(DeviceHandle &deviceHandle, const ControlSetup & setup, unsigned char *data, std::chrono::milliseconds timeout) noexcept
{
  assert(deviceHandle.libusbHandle() != nullptr);
  assert(data != nullptr);

  return libusb_control_transfer(
    deviceHandle.libusbHandle(),
    setup.bmRequestTypeValue(),
    setup.bRequestValue(),
    setup.wValueValue(),
    setup.wIndexValue(),
    data,
    setup.wLengthValue(),
    unsigned_int_from_std_chrono_milliseconds(timeout)
  );
}

void controlTransfer(DeviceHandle &deviceHandle, const ControlSetup & setup, unsigned char *data, std::chrono::milliseconds timeout)
{
  assert(deviceHandle.libusbHandle() != nullptr);
  assert(data != nullptr);

  int ret = controlTransferNoexcept(deviceHandle, setup, data, timeout);
  if(ret != 0){
    const QString msg = controlTransferTr("controlTransfer() failed with code %1: %2")
                        .arg( LibusbError::errorNameFromInt(ret) )
                        .arg( LibusbError::strerrorFromInt(ret) );
    throw LibusbRuntimeError( msg, LibusbError::errorFromInt(ret) );
  }
}

int controlTransferWithoutDataNoexcept(DeviceHandle &deviceHandle, const ControlSetup & setup, std::chrono::milliseconds timeout) noexcept
{
  assert(deviceHandle.libusbHandle() != nullptr);
  assert(setup.wLengthValue() == 0);

  unsigned char fakeData = 0;

  return controlTransferNoexcept(deviceHandle, setup, &fakeData, timeout);
}

void controlTransferWithoutData(DeviceHandle &deviceHandle, const ControlSetup & setup, std::chrono::milliseconds timeout)
{
  assert(deviceHandle.libusbHandle() != nullptr);
  assert(setup.wLengthValue() == 0);

  int ret = controlTransferWithoutDataNoexcept(deviceHandle, setup, timeout);
  if(ret != 0){
    const QString msg = controlTransferTr("controlTransferWithoutData() failed with code %1: %2")
                        .arg( LibusbError::errorNameFromInt(ret) )
                        .arg( LibusbError::strerrorFromInt(ret) );
    throw LibusbRuntimeError( msg, LibusbError::errorFromInt(ret) );
  }
}

}} // namespace Mdt{ namespace Usb{
