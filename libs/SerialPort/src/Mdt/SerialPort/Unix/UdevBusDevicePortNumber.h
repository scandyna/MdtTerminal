// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_UNIX_UDEV_BUS_DEVICE_PORT_NUMBER_H
#define MDT_SERIAL_PORT_UNIX_UDEV_BUS_DEVICE_PORT_NUMBER_H

#include "Mdt/SerialPort/UsbVendorIdProductId.h"
#include "Mdt/SerialPort/Unix/UdevDevice.h"
#include "mdt_serialport_export.h"
#include <cstdint>
#include <optional>
#include <filesystem>

namespace Mdt{ namespace SerialPort{ namespace Unix{

  /*! \brief Bus number, device number and port number
   */
  struct MDT_SERIALPORT_EXPORT UdevBusDevicePortNumber
  {
    /*! \brief Bus number
     *
     * This bus number refers to the Udev busnum attribute,
     * and also matches libusb_get_bus_number().
     */
    uint8_t busNumber = 0;

    /*! \brief Device number
     *
     * This device number refers to the Udev devnum attribute,
     * and also matches libusb_get_device_address().
     */
    uint8_t deviceNumber = 0;

    /*! \brief Port number
     *
     * This port number refers to the Udev port_number attribute.
     * This correspond to the port for multi-port USB serial devices.
     */
    uint8_t portNumber = 0;

    /*! \brief Check if all attributes have a value
     */
    bool isComplete() const noexcept;
  };

  /*! \brief Find the bus, device and port number
   */
  [[deprecated]]
  MDT_SERIALPORT_EXPORT
  std::optional<UdevBusDevicePortNumber> findBusDevicePortNumber(const UdevDevice & device, const UsbVendorIdProductId & vidPid);

  /*! \brief Find the bus, device and port number for given path
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
  [[deprecated]]
  MDT_SERIALPORT_EXPORT
  std::optional<UdevBusDevicePortNumber> findBusDevicePortNumberFromPath(const std::filesystem::path & path, const UsbVendorIdProductId & vidPid);

}}} // namespace Mdt{ namespace SerialPort{ namespace Unix{

#endif // #ifndef MDT_SERIAL_PORT_UNIX_UDEV_BUS_DEVICE_PORT_NUMBER_H
