// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_H
#define MDT_SERIAL_PORT_SETTINGS_H

#include "mdt_serialport_export.h"
#include <QSerialPort>
#include <QString>
#include <QtGlobal>

namespace Mdt{ namespace SerialPort{

  /*! \brief Serial port settings
   *
   * Settings is a set of attributes required to open a serial port.
   */
  class MDT_SERIALPORT_EXPORT Settings
  {
    friend class SettingsBuilder;

   public:

    /*! \brief Get the port name
     */
    const QString & portName() const noexcept
    {
      return mPortName;
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

    /*! \brief Get default settings
     */
    static
    Settings defaultSettings() noexcept;

   private:

    Settings() noexcept = default;

    /*! \brief Set the port name
     */
    void setPortName(const QString & name) noexcept;

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

    QString mPortName;
    qint32 mBaudRate = 0;
    QSerialPort::DataBits mDataBits = QSerialPort::UnknownDataBits;
    QSerialPort::Parity mParity = QSerialPort::UnknownParity;
    QSerialPort::FlowControl mFlowControl = QSerialPort::UnknownFlowControl;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_H
