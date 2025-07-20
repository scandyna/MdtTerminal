// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PORT_SETUP_H
#define MDT_SERIAL_PORT_PORT_SETUP_H

#include "Mdt/SerialPort/Settings.h"
#include "Mdt/SerialPort/Interface.h"
#include "Mdt/SerialPort/UsbVendorIdProductId.h"
#include "mdt_serialport_export.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QObject>
#include <memory>

#include "Mdt/SerialPort/QRuntimeError.h"
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Port setup error
   *
   * \todo should go to its own TU
   */
  class MDT_SERIALPORT_EXPORT PortSetupError : public QRuntimeError
  {
   public:

    /*! \brief Constructor
     */
    explicit
    PortSetupError(const QString & what)
      : QRuntimeError(what)
    {
    }
  };


  /*! \internal
   */
  class PortSetupImpl;

  /*! \brief Helper to set settings to a serial port
   *
   * \todo Should getting/setting some HW settings,
   * like interface, be done here ?
   * This would require to do a basic open..
   *
   * \section SerialPort_PortSetup_ConfigureMoxaUportInterfaceLinux Configure a Moxa Uport interface on Linux
   *
   * Configure the interface on %Linux has some story,
   * explained here:
   * \ref SerialPort_Linux_MoxaUPort_ConfigureMoxaUportInterfaceLinux
   *
   *
   * \sa shouldConfigureInterfaceBeforeOpenPort()
   * \sa configureInterfaceBeforeOpenPort()
   * \sa configureInterfaceOncePortOpen()
   */
  class MDT_SERIALPORT_EXPORT PortSetup : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Construct a port setup
     *
     * Depending on the platform,
     * some driver features / attributes will be fetched.
     * This is done to help for some tasks,
     * like configure the interface.
     *
     * \pre \a portInfo must have a system location
     *
     * \exception 
     */
    explicit
    PortSetup(const QSerialPortInfo & portInfo, QObject *parent = nullptr);

    /*! \brief Destructor
     */
    ~PortSetup() noexcept;

    /*! \brief Fetch some driver features
     *
     * For some cases, like Moxa UPort on Linux,
     * . 
     *
     * \todo For the Linux case, we need at least port path + PID, VID .
     * They are lost (not available in QSerialPort).
     * See how Qt get them with udev
     * hmm.. should keep PID, VID somewhere and reuse..
     * 
     * Think we should take a QSerialPortInfo here
     * Also, we could make a constructor taking a QSerialPortInfo.
     *
     * \pre \a port must not be open
     * \pre \a port must have a port name
     *
     * \exception 
     */
    [[deprecated]]
    void fetchDriverFeatures(QSerialPort & port);

    /*! \brief Check if the interface should be configured before open the port
     *
     * Returns true for special cases that require to configure
     * the interface before open the serial port,
     * otherwise false.
     */
    bool shouldConfigureInterfaceBeforeOpenPort() const;

    /*! \brief Configure the interface before open the port
     *
     * \pre It must be required to configure the interface before port is open
     * \sa shouldConfigureInterfaceBeforeOpenPort()
     *
     * \exception PortSetupError
     */
    void configureInterfaceBeforeOpenPort(const Interface & interface);

    /*! \brief Configure the interface once the port is open
     *
     * \pre \a port must be open
     *
     * \exception PortSetupError
     */
    void configureInterfaceOncePortOpen(const Interface & interface, QSerialPort & port);

    /*! \brief Configure the interface for given port
     *
     * \exception PortSetupError
     * \pre \a port must be open
     */
    [[deprecated]]
    static
    void configureInterface(const Interface & interface, QSerialPort & port);

    /*! \brief Set given settings to given port
     *
     * \pre \a port must not be open
     */
    static
    void setSettingsToPort(const Settings & settings, QSerialPort & port);

    /*! \brief Get settings from given port
     */
    static
    Settings getSettingsFromPort(const QSerialPort & port);

    /*! \brief Check if given port info has a vendor and a product identifier
     */
    static
    bool hasVidAndPid(const QSerialPortInfo & portInfo) noexcept;

    /*! \brief Check if given port info represents a Moxa UPort 1250, 1450 or 1650 series
     *
     * \sa \ref SerialPort_Device_MoxaUPort_ModuleFunctions
     */
    static
    bool isMoxaUPort_1250_1450_1650(const QSerialPortInfo & portInfo) noexcept;

    /*! \brief Get an USB vendor and product identifier from given port info
     *
     * \pre \a portInfo must have a vendor and product identifier
     * \sa hasVidAndPid()
     */
    static
    UsbVendorIdProductId usbVendorIdProductIdFromPortInfo(const QSerialPortInfo & portInfo) noexcept;

   private:

    std::unique_ptr<PortSetupImpl> mImpl;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PORT_SETUP_H
