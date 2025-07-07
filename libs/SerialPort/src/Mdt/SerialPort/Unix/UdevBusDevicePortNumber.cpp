// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "UdevBusDevicePortNumber.h"
#include "UdevTree.h"
#include "UdevContext.h"
#include "FileStatus.h"
#include <memory>
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace Unix{

bool UdevBusDevicePortNumber::isComplete() const noexcept
{
  if(busNumber == 0){
    return false;
  }
  if(deviceNumber == 0){
    return false;
  }
  // if(portNumber == 0){
  //   return false;
  // }

  return true;
}


std::optional<UdevBusDevicePortNumber> findBusDevicePortNumber(const UdevDevice & device, const UsbVendorIdProductId & vidPid)
{
  UdevBusDevicePortNumber result;
  bool found = false;

  /*
   * We start at a leaf of the device tree.
   * Walk up until we find the expected device.
   * If we walk more, we will probably en up to a PCI controller.
   * On the road, we also will get the port number of the device.
   */

  const auto f = [&result](udev_device *devicePtr)
  {
    const auto bus = UdevDevice::getBusNumber(devicePtr);
    if( bus.has_value() ){
      result.busNumber = *bus;
    }

    const auto devnum = UdevDevice::getDeviceNumber(devicePtr);
    if( devnum.has_value() ){
      result.deviceNumber = *devnum;
    }

    const auto port = UdevDevice::getPortNumber(devicePtr);
    if( port.has_value() ){
      result.portNumber = *port;
    }
  };

  const auto pred = [vidPid, &found](udev_device *devicePtr) -> bool
  {
    found =  UdevDevice::deviceMatchesVidPid(devicePtr, vidPid);
    return found;
  };

  walkUdevTreeToRootUntil(device, f, pred);

  if( !found ){
    return {};
  }
  assert( result.isComplete() );

  return result;
}

std::optional<UdevBusDevicePortNumber> findBusDevicePortNumberFromPath(const std::filesystem::path & path, const UsbVendorIdProductId & vidPid)
{
  const auto fileStatus = FileStatus::fromPath(path);

  const auto udevContext = std::make_shared<UdevContext>();

  auto device = UdevDevice::from_devnum( udevContext, fileStatus.fileType(), fileStatus.representedDeviceId() );

  return findBusDevicePortNumber(device, vidPid);
}

}}} // namespace Mdt{ namespace SerialPort{ namespace Unix{
