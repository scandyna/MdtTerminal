// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_DEVICE_MOXA_UPORT_H
#define MDT_SERIAL_PORT_DEVICE_MOXA_UPORT_H

#include "Mdt/SerialPort/InterfaceStandard.h"
#include "mdt_serialport_export.h"
#include <cstdint>
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace Device{

  /*! \page SerialPort_Device_MoxaUPort Moxa UPort
   *
   * \sa https://www.moxa.com/en/products/industrial-edge-connectivity/usb-to-serial-converters-usb-hubs/usb-to-serial-converters
   *
   * \section SerialPort_Device_MoxaUPort_ModuleFunctions Moxa UPort module functions
   *
   * This module provides theses functions:
   * - vendorIdentifierIsMoxa()
   * - productIdentifierIsMoxaUPort_1250_1450_1650()
   * - interfaceStandardFromMoxaUport_1250_1450_1650_ParameterValue()
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
   * |UPort 1110   |0x1???|  1  |  X   |      |      |
   * |UPort 1130   |0x1???|  1  |      |  X   |  X   |
   * |UPort 1130I  |0x1???|  1  |      |  X   |  X   |
   * |UPort 1150   |0x1???|  1  |  X   |  X   |  X   |
   * |UPort 1150I  |0x1???|  1  |  X   |  X   |  X   |
   *
   *
   * \section SerialPort_Device_MoxaUPort_LinuxSpecific Moxa UPort Linux specific
   *
   * See the dedicated page: \ref SerialPort_Linux_MoxaUPort
   *
   *
   * \section SerialPort_Device_MoxaUPort_WindowsSpecific Moxa UPort Windows specific
   *
   * An attempt to set/get the interface has been done. See this commit :
   * https://gitlab.com/scandyna/mdtterminal/-/commit/de5b6489d222d789120f84029d7ee2e30bc89a82
   * This fails with error code 1: \c ERROR_INVALID_FUNCTION.
   * \c DeviceIoControl calls to set/get the interface will not work on COM handle
   * because the virtual port driver does not export configuration endpoints.
   *
   * The official Moxa Windows driver architecture separates data I/O from hardware topology configuration,
   * routing physical layer changes through proprietary user-space DLLs (\c mxusport.dll / \c mxusbrd.dll)
   * that interact with the Windows Registry.
   * The driver persists the device setup, like the selected interface.
   * After unplug / re-plug, or reboot, the driver will setup the device with the persisted state.
   *
   * There seems to be **no way** to read the setup from the device.
   *
   * To prevent race conditions, memory state inconsistencies within the OS,
   * and brittle dependency chains on undocumented vendor DLLs, hardware configuration under Windows
   * must be managed persistently by the OS via the %Device Manager (*Multi-port serial adapters* -> *Properties* -> *Port %Settings*).
   *
   * In the UI, the interface selection will be disabled, and display something like \a System instead of an interface, like RS-232.
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

  /*! \brief Get the interface standard for given parameter value of an UPort 1250, 1450 or 1650 series
   *
   * \pre \a parameterValue must be a value in range 0 to 3
   */
  constexpr
  InterfaceStandard interfaceStandardFromMoxaUport_1250_1450_1650_ParameterValue(uint16_t parameterValue) noexcept
  {
    assert(parameterValue <= 3);

    switch(parameterValue){
      case 0x0:
        return InterfaceStandard::RS_232;
      case 0x1:
        return InterfaceStandard::RS_485_2W;
      case 0x2:
        return InterfaceStandard::RS_422;
      case 0x3:
        return InterfaceStandard::RS_485_4W;
    }

    return InterfaceStandard::RS_232;
  }

}}} // namespace Mdt{ namespace SerialPort{ namespace Device{

#endif // #ifndef MDT_SERIAL_PORT_DEVICE_MOXA_UPORT_H
