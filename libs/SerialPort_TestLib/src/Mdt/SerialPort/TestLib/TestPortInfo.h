// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_PORT_INFO_H
#define MDT_SERIAL_PORT_TEST_LIB_TEST_PORT_INFO_H

#include "Mdt/SerialPort/PortInfo.h"
#include "mdt_serialport_testlib_export.h"

namespace Mdt{ namespace SerialPort{ namespace TestLib{

  /*! \brief Test helper class to relax Mdt::SerialPort::PortInfo
   *
   * \warning There is no virtual polymorphism used,
   *  meaning the object will be sliced.
   *  Do not add any member here.
   */
  class MDT_SERIALPORT_TESTLIB_EXPORT TestPortInfo : public Mdt::SerialPort::PortInfo
  {
   public:

    /*! \brief Constructs an empty PortInfo object.
     *
     * \sa isNull()
     */
    TestPortInfo() noexcept = default;

    /*! \brief Set the description
     */
    void setDescription(const QString & description);

    /*! \brief Set the manufacturer
     */
    void setManufacturer(const QString & manufacturer);

    /*! \brief Set the serial number
     */
    void setSerialNumber(const QString & sn);

    /*! \brief Set the VID
     */
    void setVendorIdentifier(uint16_t vid);

    /*! \brief Set the PID
     */
    void setProductIdentifier(uint16_t pid);

    /*! \brief Construct a port info from given port name and system location
     *
     * \pre \a portName and \a systemLocation must not be empty strings
     * \note Giving a non existing port is fine here
     */
    static
    TestPortInfo fromPortNameAndSystemLocation(const QString & portName, const QString & systemLocation) noexcept;

  private:

    TestPortInfo(const QString & portName, const QString & systemLocation) noexcept;
  };

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{

#endif // #ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_PORT_INFO_H
