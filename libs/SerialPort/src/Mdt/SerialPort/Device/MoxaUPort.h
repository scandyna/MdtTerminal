// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_DEVICE_MOXA_UPORT_H
#define MDT_SERIAL_PORT_DEVICE_MOXA_UPORT_H

#include "mdt_serialport_export.h"
#include <cstdint>

namespace Mdt{ namespace SerialPort{ namespace Device{

  /*! \page SerialPort_Device_MoxaUPort Moxa UPort
   *
   * \sa https://www.moxa.com/en/products/industrial-edge-connectivity/usb-to-serial-converters-usb-hubs/usb-to-serial-converters
   *
   * \section SerialPort_Device_MoxaUPort_ModuleFunctions Moxa UPort module functions
   *
   * This module provides thoses functions:
   * - vendorIdentifierIsMoxa()
   * - productIdentifierIsMoxaUPort_1250_1450_1650()
   *
   * \section SerialPort_Device_MoxaUPort_1200_1400_1600_Series Moxa UPort 1200, 1400, 1600 series (and also G2)
   *
   * The Moxa UPort (%Linux) driver should support those devices:
   *
   * |  Name             | PID  |Ports|RS-232|RS-422|RS-485|
   * |:------------------|:----:|:---:|:----:|:----:|:----:|
   * |UPort 1250         |0x1250|  2  |  X   |  X   |  X   |
   * |UPort 1250I        |0x1251|  2  |  X   |  X   |  X   |
   * |UPort 1250-G2      |0x12??|  2  |  X   |  X   |  X   |
   * |UPort 1250-G2-T    |0x12??|  2  |  X   |  X   |  X   |
   * |UPort 1250I-G2     |0x12??|  2  |  X   |  X   |  X   |
   * |UPort 1250I-G2-T   |0x12??|  2  |  X   |  X   |  X   |
   * |UPort 1410         |0x1410|  4  |  X   |      |      |
   * |UPort 1450         |0x1450|  4  |  X   |  X   |  X   |
   * |UPort 1450I        |0x1451|  4  |  X   |  X   |  X   |
   * |UPort 1410-G2      |0x1???|  4  |  X   |      |      |
   * |UPort 1450-G2      |0x1???|  4  |  X   |  X   |  X   |
   * |UPort 1450-G2-T    |0x1???|  4  |  X   |  X   |  X   |
   * |UPort 1450I-G2     |0x1???|  4  |  X   |  X   |  X   |
   * |UPort 1450I-G2-T   |0x1???|  4  |  X   |  X   |  X   |
   * |UPort 1610-8       |0x1618|  8  |  X   |      |      |
   * |UPort 1650-8       |0x1658|  8  |  X   |  X   |  X   |
   * |UPort 1610-16      |0x1613| 16  |  X   |      |      |
   * |UPort 1650-16      |0x1653| 16  |  X   |  X   |  X   |
   * |UPort 1610-8-G2    |0x1???|  8  |  X   |      |      |
   * |UPort 1650-8-G2    |0x1???|  8  |  X   |  X   |  X   |
   * |UPort 1650-8-G2-T  |0x1???|  8  |  X   |  X   |  X   |
   * |UPort 1650I-8-G2   |0x1???|  8  |  X   |  X   |  X   |
   * |UPort 1650I-8-G2-T |0x1???|  8  |  X   |  X   |  X   |
   * |UPort 1650-8-G2-Hub|0x1???|  8  |  X   |  X   |  X   |
   *
   * \note The official %Linux driver seems not to support the G2 series.
   *
   *
   * \subsection SerialPort_Device_MoxaUPort_1200_1400_1600_Series_SetInterface Set the interface
   *
   * The interface can be set with an USB control transfer with a vendor specific request type.
   * The bRquestValue must be 0x10.
   * The wValue represents the interface:
   *
   * |Parameter value|%Interface|
   * |:-------------:|:---------|
   * |      0x0      |RS-232    |
   * |      0x1      |RS-485 2W |
   * |      0x2      |RS-422    |
   * |      0x3      |RS-485 4W |
   *
   *
   * \section SerialPort_Device_MoxaUPort_1100_Series Moxa UPort 1100 series
   *
   * There is also a UPort 1100 series.
   * Moxa provides another (%Linux) driver for those interfaces.
   * They seems to be different from the above ones.
   *
   * |  Name       | PID  |Ports|RS-232|RS-422|RS-485|
   * |:------------|:----:|:---:|:----:|:----:|:----:|
   * |UPort 1110   |0x1???|  1  |      |      |      |
   * |UPort 1130   |0x1???|  1  |      |  X   |  X   |
   * |UPort 1130I  |0x1???|  1  |      |  X   |  X   |
   * |UPort 1150   |0x1???|  1  |  X   |  X   |  X   |
   * |UPort 1150I  |0x1???|  1  |  X   |  X   |  X   |
   *
   */

  /*! \brief Check if given vendor identifier is Moxa
   */
  constexpr
  bool vendorIdentifierIsMoxa(uint16_t vid) noexcept
  {
    return vid == 0x110a;
  }

  /*! \brief Check if given product identifier is a 1250, 1450 or 1650 series
   *
   * The 1250, 1450, 1650 an their G2 equivalent are devices supporting
   * RS-232, RS-422 and RS-485.
   */
  constexpr
  bool productIdentifierIsMoxaUPort_1250_1450_1650(uint16_t pid) noexcept
  {
    switch(pid){
      case 0x1250:
      case 0x1251:
      case 0x1450:
      case 0x1451:
      case 0x1658:
      case 0x1653:
        return true;
    }

    return false;
  }

}}} // namespace Mdt{ namespace SerialPort{ namespace Device{

#endif // #ifndef MDT_SERIAL_PORT_DEVICE_MOXA_UPORT_H
