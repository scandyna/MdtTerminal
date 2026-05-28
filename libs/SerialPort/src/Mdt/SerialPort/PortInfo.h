// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PORT_INFO_H
#define MDT_SERIAL_PORT_PORT_INFO_H

#include "mdt_serialport_export.h"
#include <QSerialPortInfo>
#include <QString>
#include <cstdint>
#include <optional>
#include <cassert>

namespace Mdt{ namespace SerialPort{

  /*! \brief Provides information about a serial port
   *
   * PortInfo is like QSerialPortInfo,
   * but can be relaxed for testing purposes.
   *
   * This concrete implementation
   * can only created from a QSerialPortInfo,
   * meaning from an existing serial port.
   */
  class MDT_SERIALPORT_EXPORT PortInfo
  {
   public:

    /*! \brief Constructs an empty PortInfo object.
     *
     * \sa isNull()
     */
    PortInfo() noexcept = default;

    /*! \brief Returns true for an empty port info
     *
     * This port info is null unless the port name
     * and the system location are defined.
     */
    bool isNull() const noexcept
    {
      return mPortName.isEmpty() || mSystemLocation.isEmpty();
    }

    /*! \brief Returns the name of the serial port.
     */
    QString portName() const noexcept
    {
      return mPortName;
    }

    /*! \brief Returns the system location of the serial port.
     */
    QString systemLocation() const noexcept
    {
      return mSystemLocation;
    }

    /*! \brief Returns the description string of the serial port, if available; otherwise returns an empty string.
     */
    QString description() const noexcept
    {
      return mDescription;
    }

    /*! \brief Returns the manufacturer string of the serial port, if available; otherwise returns an empty string.
     */
    QString manufacturer() const noexcept
    {
      return mManufacturer;
    }

    /*! \brief Returns the serial number string of the serial port, if available; otherwise returns an empty string.
     */
    QString serialNumber() const noexcept
    {
      return mSerialNumber;
    }

    /*! \brief Returns true if there is a valid 16-bit vendor number present; otherwise returns false.
     */
    bool hasVendorIdentifier() const noexcept
    {
      return mVendorIdentifier.has_value();
    }

    /*! \brief Returns the 16-bit vendor number for the serial port
     *
     * \pre The vendor identifier must be available
     * \sa hasVendorIdentifier()
     */
    uint16_t vendorIdentifier() const noexcept
    {
      assert( hasVendorIdentifier() );

      return *mVendorIdentifier;
    }

    /*! \brief Returns the 16-bit vendor number for the serial port if present
     */
    std::optional<uint16_t> vendorIdentifierIfAvailable() const noexcept
    {
      return mVendorIdentifier;
    }

    /*! \brief Returns true if there is a valid 16-bit product number present; otherwise returns false.
     */
    bool hasProductIdentifier() const noexcept
    {
      return mProductIdentifier.has_value();
    }

    /*! \brief Returns the 16-bit product number for the serial port
     *
     * \pre The product identifier must be available
     * \sa hasProductIdentifier()
     */
    uint16_t productIdentifier() const noexcept
    {
      assert( hasProductIdentifier() );

      return *mProductIdentifier;
    }

    /*! \brief Returns the 16-bit product number for the serial port if present
     */
    std::optional<uint16_t> productIdentifierIfAvailable() const noexcept
    {
      return mProductIdentifier;
    }

    /*! \brief Construct a PortInfo from given QSerialPortInfo
     *
     * \pre Given \a portInfo must not be null
     */
    static
    PortInfo fromQSerialPortInfo(const QSerialPortInfo & portInfo);

   protected:

    void setDescription(const QString & description);
    void setManufacturer(const QString & manufacturer);
    void setSerialNumber(const QString & sn);
    void setVendorIdentifier(uint16_t vid);
    void setProductIdentifier(uint16_t pid);

    PortInfo(const QString & portName, const QString & systemLocation) noexcept;

   private:

    QString mPortName;
    QString mSystemLocation;
    QString mDescription;
    QString mManufacturer;
    QString mSerialNumber;
    std::optional<uint16_t> mVendorIdentifier;
    std::optional<uint16_t> mProductIdentifier;
  };

  /*! \internal Check if given port info represents an existing serial port
   *
   * QSerialPortInfo::availablePorts() does such checks,
   * and should return only real serial ports.
   * On some platforms, like Ubuntu-24.04,
   * some changes (like Udev driver name changing from serial8250 to port)
   * breaks some checks.
   *
   * This function is a workaround for such issues.
   *
   * \sa https://gitlab.com/scandyna/mdtterminal/-/work_items/9
   */
  MDT_SERIALPORT_EXPORT
  bool isExistingSerialPort(const PortInfo & portInfo);

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PORT_INFO_H
