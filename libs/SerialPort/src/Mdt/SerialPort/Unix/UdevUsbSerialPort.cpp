// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "UdevUsbSerialPort.h"
#include "UdevTree.h"
#include "UdevContext.h"
#include "FileStatus.h"
#include <memory>
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace Unix{

void UdevUsbSerialPort::setUsbBusNumber(uint8_t number) noexcept
{
  assert( !hasUsbBusNumber() );

  mUsbBusNumber = number;
}

void UdevUsbSerialPort::setUsbDeviceAddress(uint8_t address) noexcept
{
  assert( !hasUsbDeviceAddress() );

  mUsbDeviceAddress = address;
}

void UdevUsbSerialPort::setPortNumber(uint8_t number) noexcept
{
  assert( !hasPortNumber() );

  mPortNumber = number;
}

uint8_t UdevUsbSerialPort::portNumber() const noexcept
{
  assert( hasPortNumber() );

  return *mPortNumber;
}

void UdevUsbSerialPort::setDriverName(const std::string & name) noexcept
{
  assert( !hasDriverName() );

  mDriverName = name;
}

bool UdevUsbSerialPort::isComplete() const noexcept
{
  return hasUsbBusNumber() && hasUsbDeviceAddress() && hasPortNumber() && hasDriverName();
}


namespace Impl{

  

} // namespace Impl{


std::optional<UdevUsbSerialPort> findUdevUsbSerialPort(const UdevDevice & device, const UsbVendorIdProductId & vidPid)
{
  UdevUsbSerialPort udevPort;
  bool found = false;

  /*
   * We start at a leaf of the device tree.
   * Walk up until we find the expected device.
   * If we walk more, we will probably en up to a PCI controller.
   * On the road, we also will get the port number of the device.
   */

  if( !found ){
    return {};
  }
  assert( udevPort.isComplete() );

  return udevPort;
}

std::optional<UdevUsbSerialPort> findUdevUsbSerialPortFromPath(const std::filesystem::path & path, const UsbVendorIdProductId & vidPid)
{
  const auto fileStatus = FileStatus::fromPath(path);

  const auto udevContext = std::make_shared<UdevContext>();

  auto device = UdevDevice::from_devnum( udevContext, fileStatus.fileType(), fileStatus.representedDeviceId() );

  return findUdevUsbSerialPort(device, vidPid);
}

}}} // namespace Mdt{ namespace SerialPort{ namespace Unix{
