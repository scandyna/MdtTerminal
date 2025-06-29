// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_UNIX_UDEV_USB_SERIAL_PORT_H
#define MDT_SERIAL_PORT_UNIX_UDEV_USB_SERIAL_PORT_H

#include "Mdt/SerialPort/UsbVendorIdProductId.h"
#include "Mdt/SerialPort/Unix/UdevDevice.h"
#include "mdt_serialport_export.h"
#include <cstdint>
#include <optional>
#include <string>
#include <filesystem>

namespace Mdt{ namespace SerialPort{ namespace Unix{

  /*! \brief Udev informations about the USB device a given serial port is part of
   *
   * A serial port, like /dev/ttyUSB0, can be part of an USB device (an USB-serial adapter).
   * Some devices, like Moxa UPort 1250, are USB devices providing multiple serial ports.
   *
   * This class is made to collect informations while walking up a Udev tree.
   *
   * \sa findUdevUsbSerialPort()
   * \sa findUdevUsbSerialPortFromPath()
   */
  class MDT_SERIALPORT_EXPORT UdevUsbSerialPort
  {
   public:

    /*! \brief Check if this port has an USB bus number
     */
    bool hasUsbBusNumber() const noexcept
    {
      return mUsbBusNumber != 0;
    }

    /*! \brief Set the USB bus number
     *
     * \pre USB bus number must not have been previously set
     * \sa hasUsbBusNumber()
     */
    void setUsbBusNumber(uint8_t number) noexcept;

    /*! \brief Get the USB bus number
     *
     * \sa setUsbBusNumber()
     */
    uint8_t usbBusNumber() const noexcept
    {
      return mUsbBusNumber;
    }

    /*! \brief Check if this port has an USB device address
     */
    bool hasUsbDeviceAddress() const noexcept
    {
      return mUsbDeviceAddress != 0;
    }

    /*! \brief Set the USB device address
     *
     * Corresponds to the Udev devnum for an USB sybsystem
     *
     * \pre the USB device address must not have been previously set
     * \sa hasUsbDeviceAddress()
     */
    void setUsbDeviceAddress(uint8_t address) noexcept;

    /*! \brief Set the USB device address
     *
     * \sa setUsbDeviceAddress()
     */
    uint8_t usbDeviceAddress() const noexcept
    {
      return mUsbDeviceAddress;
    }

    /*! \brief Check if a port number has been set
     */
    bool hasPortNumber() const noexcept
    {
      return mPortNumber.has_value();
    }

    /*! \brief Set the port number
     *
     * This port number refers to the Udev port_number attribute.
     * This correspond to the port for multi-port USB-serial devices.
     *
     * \pre the port number must not have been set previously
     * \sa hasPortNumber()
     */
    void setPortNumber(uint8_t number) noexcept;

    /*! \brief Get the port number
     *
     * \pre the port number must have been set
     * \sa hasPortNumber()
     * \sa setPortNumber()
     */
    uint8_t portNumber() const noexcept;

    /*! \brief Check if a driver name has been set
     */
    bool hasDriverName() const noexcept
    {
      return !mDriverName.empty();
    }

    /*! \brief Set the driver name
     *
     * Corresponds to the driver attribute in Udev
     *
     * \pre the driver must not have been set previously
     * \sa hasDriverName()
     */
    void setDriverName(const std::string & name) noexcept;

    /*! \brief Get the driver name
     *
     * \sa setDriverName()
     */
    const std::string driverName() const noexcept
    {
      return mDriverName;
    }

    /*! \brief Check if all attributes have a value
     */
    bool isComplete() const noexcept;

   private:

    uint8_t mUsbBusNumber = 0;
    uint8_t mUsbDeviceAddress = 0;
    std::optional<uint8_t> mPortNumber;
    std::string mDriverName;
  };

  /*! \brief Find the USB device informations for a serial port starting from given device
   */
  MDT_SERIALPORT_EXPORT
  std::optional<UdevUsbSerialPort> findUdevUsbSerialPort(const UdevDevice & device, const UsbVendorIdProductId & vidPid);

  /*! \brief Find the USB device informations for given serial port
   *
   * Example:
   * Imagine we have 2 Moxa UPort 1250 attached to the system.
   * - /dev/ttyUSB0 : bus 1, device 4, port number 0  (VID: 0x110a, PID: 0x1250)
   * - /dev/ttyUSB1 : bus 1, device 4, port number 1  (VID: 0x110a, PID: 0x1250)
   * - /dev/ttyUSB2 : bus 2, device 3, port number 0  (VID: 0x110a, PID: 0x1250)
   * - /dev/ttyUSB3 : bus 2, device 3, port number 1  (VID: 0x110a, PID: 0x1250)
   *
   * Here, the VID and PID of the device is the same for both.
   * If we want, f.ex., set the interface of ttyUSB1 to RS-422 with an USB control transfert,
   * we need to know the bus and device (address) to differentiate which device to configure,
   * and also the port number of the device.
   *
   * \note The VID and PID is required because of the way the libudev API is made.
   * See implementation for more details.
   *
   * \pre 
   * \exception 
   */
  MDT_SERIALPORT_EXPORT
  std::optional<UdevUsbSerialPort> findUdevUsbSerialPortFromPath(const std::filesystem::path & path, const UsbVendorIdProductId & vidPid);

}}} // namespace Mdt{ namespace SerialPort{ namespace Unix{

#endif // #ifndef MDT_SERIAL_PORT_UNIX_UDEV_USB_SERIAL_PORT_H
