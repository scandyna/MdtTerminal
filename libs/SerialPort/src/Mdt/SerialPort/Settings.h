// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_H
#define MDT_SERIAL_PORT_SETTINGS_H

#include "Mdt/SerialPort/PortInfo.h"
#include "Mdt/SerialPort/Platform.h"
#include "Mdt/SerialPort/Interface.h"
#include "Mdt/SerialPort/SendByteByByteSettings.h"
#include "mdt_serialport_export.h"
#include <QSerialPort>
#include <QString>
#include <QtGlobal>
#include <chrono>
#include <cassert>

namespace Mdt{ namespace SerialPort{

  /*! \brief Check if 1.5 stop bits is supported
   *
   * Returns true on Windows
   * \sa osIsWindows()
   */
  constexpr
  bool oneAndHalfStopBitsIsSupported() noexcept
  {
    return osIsWindows();
  }

  /*! \brief Serial port settings
   *
   * Settings is a set of attributes required to open a serial port.
   */
  class MDT_SERIALPORT_EXPORT Settings
  {
    friend class SettingsBuilder;

   public:

    /*! \brief Check if port info is available
     */
    bool hasPortInfo() const noexcept
    {
      return !mPortInfo.isNull();
    }

    /*! \brief Get the port info
     */
    const PortInfo & portInfo() const noexcept
    {
      return mPortInfo;
    }

    /*! \brief Get the port name
     *
     * Returns an empty string if not portinfo is available
     * \sa hasPortInfo()
     * \sa portInfo()
     */
    QString portName() const noexcept
    {
      return portInfo().portName();
    }

    /*! \brief Get the baud rate
     */
    qint32 baudRate() const noexcept
    {
      return mBaudRate;
    }

    /*! \brief Get the data bits
     */
    QSerialPort::DataBits dataBits() const noexcept
    {
      return mDataBits;
    }

    /*! \brief Get the parity
     */
    QSerialPort::Parity parity() const noexcept
    {
      return mParity;
    }

    /*! \brief Get the flow control
     */
    QSerialPort::FlowControl flowControl() const noexcept
    {
      return mFlowControl;
    }

    /*! \brief Get the stop bits
     */
    QSerialPort::StopBits stopBits() const noexcept
    {
      return mStopBits;
    }

    /*! \brief Get the interface
     */
    const Interface & interface() const noexcept
    {
      return mInterface;
    }

    /*! \brief Get the interface standard
     */
    InterfaceStandard interfaceStandard() const noexcept
    {
      return mInterface.standard();
    }

    /*! \brief Get send byte by byte settings
     */
    const SendByteByByteSettings & sendByteByByteSettings() const noexcept
    {
      return mSendByteByByteSettings;
    }

    /*! \brief Check if sending byte by byte is enabled
     *
     * \sa sendByteByByteInterval()
     */
    bool sendByteByByteIsEnabled() const noexcept
    {
      return mSendByteByByteSettings.isEnabled();
    }

    /*! \brief Get the interval between bytes
     *
     * \pre send byte by byte must be enabled
     * \sa sendByteByByteIsEnabled()
     */
    std::chrono::milliseconds sendByteByByteInterval() const noexcept
    {
      assert( sendByteByByteIsEnabled() );

      return mSendByteByByteSettings.interval();
    }

    /*! \brief Check if given baud rate has minimal validity
     *
     * Returns true if given \a rate is > 0
     * \note A real validation requires to open the serial port
     */
    static
    bool baudRateHasMinimalValidity(qint32 rate) noexcept;

    /*! \brief Check if given data bits has minimal validity
     *
     * Returns true if given \a bits is in a documented range
     * \note A real validation requires to open the serial port
     * \sa https://doc.qt.io/qt-6/qserialport.html#DataBits-enum
     */
    static
    bool dataBitsHasMinimalValidity(QSerialPort::DataBits bits) noexcept;

    /*! \brief Check if given parity has minimal validity
     *
     * Returns true if given \a parity is in a documented range
     * \note A real validation requires to open the serial port
     * \sa https://doc.qt.io/qt-6/qserialport.html#Parity-enum
     */
    static
    bool parityHasMinimalValidity(QSerialPort::Parity parity) noexcept;

    /*! \brief Check if given flow control has minimal validity
     *
     * Returns true if given \a control is in a documented range
     * \note A real validation requires to open the serial port
     * \sa https://doc.qt.io/qt-6/qserialport.html#FlowControl-enum
     */
    static
    bool flowControlHasMinimalValidity(QSerialPort::FlowControl control) noexcept;

    /*! \brief Check if given stop bits has minimal validity
     *
     * Returns true if given \a bits is supported for the platform.
     * In general, 1 or 2 stop bits is valid.
     * On Windows, 1.5 stop bits is also supported.
     * \note A real validation requires to open the serial port
     * \sa https://doc.qt.io/qt-6/qserialport.html#FlowControl-enum
     * \sa oneAndHalfStopBitsIsSupported()
     */
    static
    bool stopBitsHasMinimalValidity(QSerialPort::StopBits bits) noexcept;

    /*! \brief Get default settings
     *
     * \note Default settings has no port info
     */
    static
    Settings defaultSettings() noexcept;

    /*! \brief Get default settings with given port info
     */
    static
    Settings defaultSettingsWithPortInfo(const PortInfo & portInfo) noexcept;

   private:

    Settings() noexcept = default;
    Settings(const PortInfo & portInfo) noexcept;

    /*! \brief Set the port info
     */
    void setPortInfo(const PortInfo & portInfo) noexcept;

    /*! \brief Set the baud rate
     *
     * \pre \a rate must have a minimal validity
     * \sa baudRateHasMinimalValidity()
     */
    void setBaudRate(qint32 rate) noexcept;

    /*! \brief Set the data bits
     *
     * \pre \a bits must have a minimal validity
     * \sa dataBitsHasMinimalValidity()
     */
    void setDataBits(QSerialPort::DataBits bits) noexcept;

    /*! \brief Set the parity
     *
     * \pre \a parity must have a minimal validity
     * \sa parityHasMinimalValidity()
     */
    void setParity(QSerialPort::Parity parity) noexcept;

    /*! \brief Set the flow control
     *
     * \pre \a control must have a minimal validity
     * \sa flowControlHasMinimalValidity()
     */
    void setFlowControl(QSerialPort::FlowControl control) noexcept;

    /*! \brief Set the stop bits
     *
     * \pre \a bits must have a minimal validity
     * \sa stopBitsHasMinimalValidity()
     */
    void setStopBits(QSerialPort::StopBits bits) noexcept;

    /*! \brief Set the interface
     */
    void setInterface(const Interface & interface) noexcept;

    /*! \brief Set the send byte by byte settings
     */
    void setSendByteByByteSettings(const SendByteByByteSettings & s) noexcept;

    PortInfo mPortInfo;
    qint32 mBaudRate = 9600;
    QSerialPort::DataBits mDataBits = QSerialPort::Data8;
    QSerialPort::Parity mParity = QSerialPort::NoParity;
    QSerialPort::FlowControl mFlowControl = QSerialPort::NoFlowControl;
    QSerialPort::StopBits mStopBits = QSerialPort::OneStop;
    Interface mInterface;
    SendByteByByteSettings mSendByteByByteSettings = SendByteByByteSettings::disabled();
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_H
