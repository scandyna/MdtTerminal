// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "UdevDevice.h"
#include "Mdt/SerialPort/StringHelpers.h"
#include <QString>
#include <QCoreApplication>
#include <errno.h>
// #include <string.h>
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace Linux{

using Mdt::SerialPort::Unix::FileStatusFileType;


QString udevDeviceTr(const char *sourceText) noexcept
{
  return QCoreApplication::translate("Mdt::SerialPort::Unix::UdevDevice", sourceText);
}


UdevDevice::~UdevDevice() noexcept
{
  udev_device_unref(mDevice);
}

UdevDevice UdevDevice::from_devnum(std::shared_ptr<UdevContext> context, FileStatusFileType type, dev_t devnum)
{
  assert(context != nullptr);

  char deviceTypeChar = deviceTypeCharFromFileType(type);
  if(deviceTypeChar == '\0'){
    QString msg = udevDeviceTr("get an udev device failed for devnum %1 : given type is not supported (should be block device or character device)")
                  .arg(devnum);
    throw FileOpenError(msg);
  }

  udev_device *device = udev_device_new_from_devnum(context->nativePointer(), deviceTypeChar, devnum);
  if(device == nullptr){
    QString msg = udevDeviceTr("get an udev device failed for devnum %1 : %2")
                  .arg(devnum)
                  .arg( QString::fromLocal8Bit( strerror(errno) ) );
    throw FileOpenError(msg);
  }

  return UdevDevice(context, device);
}

char UdevDevice::deviceTypeCharFromFileType(FileStatusFileType type) noexcept
{
  switch(type){
    case FileStatusFileType::BlockDevice:
      return 'b';
    case FileStatusFileType::CharacterDevice:
      return 'c';
    default:
      break;
  }

  return '\0';
}

std::string UdevDevice::getSystemName(udev_device *device)
{
  assert(device != nullptr);

  const char *str = udev_device_get_sysname(device);

  return stdStringFromCString(str, 30);
}

std::string UdevDevice::getSubsystem(udev_device *device)
{
  assert(device != nullptr);

  const char *str = udev_device_get_subsystem(device);

  return stdStringFromCString(str, 30);
}

std::string UdevDevice::getDriver(udev_device *device)
{
  assert(device != nullptr);

  const char *str = udev_device_get_driver(device);

  return stdStringFromCString(str, 30);
}

std::string UdevDevice::getDeviceType(udev_device *device)
{
  assert(device != nullptr);

  const char *str = udev_device_get_devtype(device);

  return stdStringFromCString(str, 50);
}

std::optional<uint8_t> UdevDevice::getBusNumber(udev_device *device)
{
  assert(device != nullptr);

  return getSystemAttribute_uint8_t_Value(device, "busnum", 10);
}

std::optional<uint8_t> UdevDevice::getDeviceNumber(udev_device *device)
{
  assert(device != nullptr);

  return getSystemAttribute_uint8_t_Value(device, "devnum", 10);
}

std::optional<uint8_t> UdevDevice::getPortNumber(udev_device *device)
{
  assert(device != nullptr);

  return getSystemAttribute_uint8_t_Value(device, "port_number", 10);
}

std::optional<uint16_t> UdevDevice::getVendorId(udev_device *device)
{
  assert(device != nullptr);

  return getSystemAttribute_uint16_t_Value(device, "idVendor", 16);
}

std::optional<uint16_t> UdevDevice::getProductId(udev_device *device)
{
  assert(device != nullptr);

  return getSystemAttribute_uint16_t_Value(device, "idProduct", 16);
}

std::optional<UsbVendorIdProductId> UdevDevice::getVendorIdProductId(udev_device *device)
{
  assert(device != nullptr);

  const auto vid = getVendorId(device);
  if( !vid.has_value() ){
    return {};
  }
  const auto pid = getProductId(device);
  if( !pid.has_value() ){
    return {};
  }

  return UsbVendorIdProductId{*vid, *pid};
}

bool UdevDevice::deviceMatchesVidPid(udev_device *device, const UsbVendorIdProductId & vidPid)
{
  assert(device != nullptr);

  const auto deviceVidPid = getVendorIdProductId(device);
  if( !deviceVidPid.has_value() ){
    return false;
  }

  return *deviceVidPid == vidPid;
}

std::optional<uint8_t> UdevDevice::getSystemAttribute_uint8_t_Value(udev_device *device, const char *attribute, int base)
{
  assert(device != nullptr);
  assert(attribute != nullptr);
  assert(stringLength(attribute, 10) > 0);
  assert( base >= 0 );
  assert( base <= 36 );

  const std::string value = getSystemAttributeStringValue(device, attribute);
  if( value.empty() ){
    return {};
  }

  return uint8_t_valueFromString(value, base);
}

std::optional<uint16_t> UdevDevice::getSystemAttribute_uint16_t_Value(udev_device *device, const char *attribute, int base)
{
  assert(device != nullptr);
  assert(attribute != nullptr);
  assert(stringLength(attribute, 10) > 0);
  assert( base >= 0 );
  assert( base <= 36 );

  const std::string value = getSystemAttributeStringValue(device, attribute);
  if( value.empty() ){
    return {};
  }

  return uint16_t_valueFromString(value, base);
}

std::string UdevDevice::getSystemAttributeStringValue(udev_device *device, const char *attribute)
{
  assert(device != nullptr);
  assert(attribute != nullptr);
  assert(stringLength(attribute, 10) > 0);

  const char *str = udev_device_get_sysattr_value(device, attribute);

  return stdStringFromCString(str, 10);
}

std::string UdevDevice::stdStringFromCString(const char *cString, size_t maxLength)
{
  const size_t len = stringLength(cString, maxLength);
  if(len == 0){
    return std::string();
  }
  assert(cString != nullptr);

  return std::string(cString, len);
}

UdevDevice::UdevDevice(std::shared_ptr<UdevContext> context, udev_device * device)
 : mContext(context),
   mDevice(device)
{
  assert(mContext != nullptr);
  assert(mDevice != nullptr);
}

}}} // namespace Mdt{ namespace SerialPort{ namespace Linux{
