// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_LINUX_UDEV_DEVICE_H
#define MDT_SERIAL_PORT_LINUX_UDEV_DEVICE_H

#include "Mdt/SerialPort/Unix/FileStatusFileType.h"
#include "Mdt/SerialPort/Linux/UdevContext.h"
#include "Mdt/SerialPort/FileOpenError.h"
#include "Mdt/SerialPort/UsbVendorIdProductId.h"
#include "mdt_serialport_export.h"
#include <libudev.h>
#include <string>
#include <optional>
#include <memory>
#include <cstdint>

namespace Mdt{ namespace SerialPort{ namespace Linux{

  /*! \brief Wrapper around an Udev device (udev_device)
   *
   * \sa https://man7.org/linux/man-pages/man3/udev_device_new_from_syspath.3.html
   * \sa https://manpages.debian.org/stretch-backports/libudev-dev/udev_device_get_property_value.3.en.html
   * \sa https://manpages.debian.org/testing/libudev-dev/udev_device_get_driver.3.en.html
   */
  class MDT_SERIALPORT_EXPORT UdevDevice
  {
   public:

    /*! \brief Free the device
     */
    ~UdevDevice() noexcept;

    UdevDevice(const UdevDevice &) = delete;
    UdevDevice & operator=(const UdevDevice &) = delete;

    UdevDevice(UdevDevice &&) = delete;
    UdevDevice & operator=(UdevDevice &&) = delete;

    /*! \brief Get the udev native pointer
     */
    udev_device *nativePointer() const noexcept
    {
      return mDevice;
    }

    /*! \brief Get a device from given type and devnum
     *
     * This is a wrapper around udev_device_new_from_devnum()
     *
     * \exception FileOpenError
     * \pre \a context must be valid
     */
    static
    UdevDevice from_devnum(std::shared_ptr<UdevContext> context, Mdt::SerialPort::Unix::FileStatusFileType type, dev_t devnum);

    /*! \brief Get the char device type representing given type
     *
     * The returned char is meant to be used with
     * udev_device_new_from_devnum() type argument.
     *
     * If \a type does not represent a usable type,
     * a null char is returned.
     */
    static
    char deviceTypeCharFromFileType(Mdt::SerialPort::Unix::FileStatusFileType type) noexcept;

    /*! \brief Get the system name (sysname)
     *
     * \note udevadm calls this KERNELS
     *
     * \pre \a device must be valid
     */
    static
    std::string getSystemName(udev_device *device);

    /*! \brief Get the subsystem
     *
     * Can return an empty string
     *
     * \pre \a device must be valid
     */
    static
    std::string getSubsystem(udev_device *device);

    /*! \brief Check if given string represents an USB subsystem
     */
    static
    bool isUsbSubsystem(const std::string & subsystem) noexcept;

    /*! \brief Get the driver
     *
     * Can return an empty string
     *
     * \pre \a device must be valid
     */
    static
    std::string getDriver(udev_device *device);

    /*! \brief Get the device type (devtype)
     *
     * Can return an empty string
     *
     * \pre \a device must be valid
     */
    static
    std::string getDeviceType(udev_device *device);

    /*! \brief Get the bus number (busnum)
     *
     * \pre \a device must be valid
     * \exception std::invalid_argument if the busnum attribute is not empty but is not a numeric value
     * \exception std::out_of_range if the converted value would fall out of the range of the uint8_t
     */
    static
    std::optional<uint8_t> getBusNumber(udev_device *device);

    /*! \brief Get the device number (devnum)
     *
     * \pre \a device must be valid
     * \exception std::invalid_argument if the devnum attribute is not empty but is not a numeric value
     * \exception std::out_of_range if the converted value would fall out of the range of the uint8_t
     */
    static
    std::optional<uint8_t> getDeviceNumber(udev_device *device);

    /*! \brief Get the port number (port_number)
     *
     * As example, for a USB - Serial (RS-232, ...) device
     * providing more than 1 port (like a Moxa UPort 1250),
     * this could represent the port index of the USB device.
     * Example:
     * - ttyUSB0 : bus 1, device 4, port number 0
     * - ttyUSB1 : bus 1, device 4, port number 1
     * - ttyUSB2 : bus 2, device 3, port number 0
     * - ttyUSB3 : bus 2, device 3, port number 1
     *
     * \pre \a device must be valid
     * \exception std::invalid_argument if the port_number attribute is not empty but is not a numeric value
     * \exception std::out_of_range if the converted value would fall out of the range of the uint8_t
     */
    static
    std::optional<uint8_t> getPortNumber(udev_device *device);

    /*! \brief Get the vendor ID (idVendor)
     *
     * \pre \a device must be valid
     * \exception std::invalid_argument if the idVendor attribute is not empty but is not a numeric value
     * \exception std::out_of_range if the converted value would fall out of the range of the uint8_t
     */
    static
    std::optional<uint16_t> getVendorId(udev_device *device);

    /*! \brief Get the product ID (idProduct)
     *
     * \pre \a device must be valid
     * \exception std::invalid_argument if the idProduct attribute is not empty but is not a numeric value
     * \exception std::out_of_range if the converted value would fall out of the range of the uint8_t
     */
    static
    std::optional<uint16_t> getProductId(udev_device *device);

    /*! \brief Get the vendor ID (idVendor) and the product ID (idProduct)
     *
     * \pre \a device must be valid
     * \sa getVendorId(udev_device *device)
     * \sa getProductId(udev_device *device)
     * \note If either the vendor ID or the product ID is missing,
     * no value is returned.
     */
    static
    std::optional<UsbVendorIdProductId> getVendorIdProductId(udev_device *device);

    /*! \brief Check if given device matches given vendor ID and product ID
     *
     * \pre \a device must be valid
     */
    static
    bool deviceMatchesVidPid(udev_device *device, const UsbVendorIdProductId & vidPid);

    /*! \brief Get an uint8_t value from given string
     *
     * If given string is empty, no value is returned.
     *
     * \todo what about nullptr ?
     *
     * \exception 
     */
    // static
    // std::optional<uint8_t> uint8_t_valueFromString(const char *str);

   private:

    /*! \brief Get the value for given system attribute
     *
     * \pre \a device must be valid
     * \pre \a attribute must not be empty and must be a valid pointer
     * \pre \a base must be in range 0 to 36
     * \exception std::invalid_argument if the value for given attribute is not empty but is not a numeric value
     * \exception std::out_of_range if the converted value would fall out of the range of the uint8_t
     */
    static
    std::optional<uint8_t> getSystemAttribute_uint8_t_Value(udev_device *device, const char *attribute, int base);

    /*! \brief Get the value for given system attribute
     *
     * \pre \a device must be valid
     * \pre \a attribute must not be empty and must be a valid pointer
     * \pre \a base must be in range 0 to 36
     * \exception std::invalid_argument if the value for given attribute is not empty but is not a numeric value
     * \exception std::out_of_range if the converted value would fall out of the range of the uint8_t
     */
    static
    std::optional<uint16_t> getSystemAttribute_uint16_t_Value(udev_device *device, const char *attribute, int base);

    static
    std::string getSystemAttributeStringValue(udev_device *device, const char *attribute);

    /*! \brief Get a std::string from given C string
     *
     * Returns an empty string if \a cString is a nullptr
     *
     * \todo should go to StringHelpers
     */
    static
    std::string stdStringFromCString(const char *cString, size_t maxLength);

    explicit
    UdevDevice(std::shared_ptr<UdevContext> context, udev_device * device);

    std::shared_ptr<UdevContext> mContext;
    udev_device *mDevice;
  };

}}} // namespace Mdt{ namespace SerialPort{ namespace Linux{

#endif // #ifndef MDT_SERIAL_PORT_LINUX_UDEV_DEVICE_H
