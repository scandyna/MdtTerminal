// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PORT_SETUP_H
#define MDT_SERIAL_PORT_PORT_SETUP_H

#include "Mdt/SerialPort/PortInfo.h"
#include "Mdt/SerialPort/Settings.h"
#include "Mdt/SerialPort/Interface.h"
#include "Mdt/SerialPort/UsbVendorIdProductId.h"
#include "Mdt/SerialPort/PortSetupError.h"
#include "Mdt/SerialPort/FileOpenError.h"
#include "mdt_serialport_export.h"
#include <QSerialPort>
#include <QObject>
#include <memory>


namespace Mdt{ namespace SerialPort{

  /*! \internal
   */
  class PortSetupImpl;

  /*! \brief Helper to set settings to a serial port ?
   *
   * \code
   * 
   * setSettings() with port info + settings
   * 
   * \endcode
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
     * \exception FileOpenError If the port referenced by \a portInfo
     *  no longer exists (f.ex: USB device has been removed).
     */
    explicit
    PortSetup(const PortInfo & portInfo, QObject *parent = nullptr);

    PortSetup(const PortSetup &) = delete;
    const PortSetup & operator=(const PortSetup &) = delete;
    PortSetup(PortSetup &&) = delete;
    PortSetup & operator=(PortSetup &&) = delete;

    /*! \brief Destructor
     */
    ~PortSetup() noexcept;

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
    bool hasVidAndPid(const PortInfo & portInfo) noexcept;

    /*! \brief Check if given port info represents a Moxa UPort 1250, 1450 or 1650 series
     *
     * \sa \ref SerialPort_Device_MoxaUPort_ModuleFunctions
     */
    static
    bool isMoxaUPort_1250_1450_1650(const PortInfo & portInfo) noexcept;

    /*! \brief Get an USB vendor and product identifier from given port info
     *
     * \pre \a portInfo must have a vendor and product identifier
     * \sa hasVidAndPid()
     */
    static
    UsbVendorIdProductId usbVendorIdProductIdFromPortInfo(const PortInfo & portInfo) noexcept;

   private:

    std::unique_ptr<PortSetupImpl> mImpl;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PORT_SETUP_H
