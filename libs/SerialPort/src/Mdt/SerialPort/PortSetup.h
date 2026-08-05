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

  /*! \brief Helper to setup a serial port
   *
   * For simple cases, PortSetup can be used as a helper,
   * with the stateless API:
   * \code
   * bool openPort(QSerialPort & port, const Settings & settings)
   * {
   *   PortSetup::setSettingsToPort(settings, port);
   *   if( !port.open(QIODevice::ReadWrite) ){
   *     return false;
   *   }
   *
   *   return true;
   * }
   * \endcode
   *
   * To handle some more advanced features,
   * like setting the interface for serial port devices that support it,
   * PortSetup can also be used:
   * \code
   * bool openPort(QSerialPort & port, const Settings & settings)
   * {
   *   PortSetup ps;
   *
   *   try{
   *     ps.fetchPortInformations( settings.portInfo() );
   *   }catch(const FileOpenError & error){
   *     return false;
   *   }
   *
   *   try{
   *     ps.configureInterfaceBeforeOpenPortIfRequired( settings.interface() );
   *   }catch(const PortSetupError & error){
   *     return false;
   *   }
   *
   *   ps.setSettingsToPort(settings, port);
   *
   *   if( !port.open(QIODevice::ReadWrite) ){
   *     return false;
   *   }
   *
   *   try{
   *     ps.configureInterfaceOncePortOpenIfRequired(settings.interface(), port);
   *   }catch(const PortSetupError & error){
   *     return false;
   *   }
   *
   *   return true;
   * }
   * \endcode
   *
   * \par Some Moxa UPort specific notes
   *
   * To see some specific informations, see this section:
   * \ref SerialPort_Device_MoxaUPort
   *
   * Configure the interface on %Linux has some story,
   * explained here:
   * \ref SerialPort_Linux_MoxaUPort_ConfigureMoxaUportInterfaceLinux
   *
   * Some choices also have been made for Windows, explained here:
   * \ref SerialPort_Device_MoxaUPort_WindowsSpecific
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
     */
    explicit
    PortSetup(QObject *parent = nullptr);

    PortSetup(const PortSetup &) = delete;
    const PortSetup & operator=(const PortSetup &) = delete;
    PortSetup(PortSetup &&) = delete;
    PortSetup & operator=(PortSetup &&) = delete;

    /*! \brief Destructor
     */
    ~PortSetup() noexcept;

    /*! \brief Fetch port informations
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
    void fetchPortInformations(const PortInfo & portInfo);

    /*! \brief Check if the interface should be configured before open the port
     *
     * Returns true for special cases that require to configure
     * the interface before open the serial port,
     * otherwise false.
     *
     * \pre fetchPortInformations() must have been called successfully
     *
     * \sa configureInterfaceBeforeOpenPortIfRequired()
     */
    bool shouldConfigureInterfaceBeforeOpenPort() const;

    /*! \brief Configure the interface before open the port
     *
     * \pre It must be required to configure the interface before port is open
     * \sa shouldConfigureInterfaceBeforeOpenPort()
     * \sa configureInterfaceBeforeOpenPortIfRequired()
     *
     * \exception PortSetupError
     */
    void configureInterfaceBeforeOpenPort(const Interface & interface);

    /*! \brief Configure the interface before open the port if required
     *
     * If given \a interface is not configurable, nothing is done.
     * Otherwise, if the interface has to be configured before open the port,
     * it will be done.
     *
     * \note fetchPortInformations() should have been called
     * successfully before, otherwise nothing will be done.
     *
     * \exception PortSetupError
     * \sa shouldConfigureInterfaceBeforeOpenPort()
     * \sa configureInterfaceBeforeOpenPort()
     */
    void configureInterfaceBeforeOpenPortIfRequired(const Interface & interface);

    /*! \brief Configure the interface once the port is open
     *
     * \pre \a port must be open
     * \exception PortSetupError
     */
    void configureInterfaceOncePortOpen(const Interface & interface, QSerialPort & port);

    /*! \brief Configure the interface once the port is open if required
     *
     * If given \a interface is not configurable, nothing is done.
     * If the interface has to be configured before open the port,
     * nothing is done.
     *
     * \pre \a port must be open
     * \exception PortSetupError
     *
     * \sa configureInterfaceOncePortOpen()
     * \sa shouldConfigureInterfaceBeforeOpenPort()
     */
    void configureInterfaceOncePortOpenIfRequired(const Interface & interface, QSerialPort & port);

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
