// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_INTERFACE_LIST_H
#define MDT_SERIAL_PORT_INTERFACE_LIST_H

#include "Mdt/SerialPort/Interface.h"
#include "Mdt/SerialPort/InterfaceStandard.h"
#include "mdt_serialport_export.h"
#include <QtGlobal>
#include <vector>
#include <optional>
#include <cassert>

namespace Mdt{ namespace SerialPort{

  /*! \brief List of supported interfaces
   *
   * Some serial port adapters provides multiple interfaces,
   * like RS-232, RS-485, etc..
   *
   * An example of such adapters are the
   * UPort 1200/1400/1600 Series from Moxa.
   *
   * We can have following cases:
   * 1. The port has 1 interface and its known by the port model (typical: UART RS-232, Moxa UPort 1110: RS-232)
   * 2. The port has more than 1 interface and we can set it
   * 3. The port has more than 1 interface, but we cannot get nor set it, its handled by the system
   *
   * \sa InterfaceListTableModel
   * \sa \ref SerialPort_DeviceSpecifics
   */
  class MDT_SERIALPORT_EXPORT InterfaceList
  {
   public:

    /*! \brief STL size_type
     */
    using size_type = std::vector<Interface>::size_type;

    /*! \brief Construct a default interface list
     *
     * By default, only the RS-232 interface is present,
     * and its not configurable.
     */
    explicit
    InterfaceList();

    /*! \brief Get the count of interfaces
     */
    size_type count() const noexcept
    {
      return mList.size();
    }

    /*! \brief Get the interface at given index
     *
     * \pre \a index must be in range
     */
    const Interface & interfaceAt(size_type index) const noexcept
    {
      assert( index < count() );

      return mList[index];
    }

    /*! \brief Check if its possible to select the interface
     */
    bool canSelectInterface() const noexcept
    {
      return count() > 1;
    }

    /*! \brief Returns true if the interface can only be handled by the system
     *
     * For some combinations of HW and platform,
     * the only viable way to handle the interface of the serial adapter
     * is to use the system: the OS, the manufacturer provided driver and tool
     * (like Moxa UPort on Windows).
     */
    bool isSystemHandledOnly() const noexcept
    {
      return (count() == 1) && (interfaceAt(0).standard() == InterfaceStandard::System);
    }

    /*! \brief Find the index of given parameter value
     *
     * Return a valid index if an interface with given \a value exists,
     * otherwise an object without any index.
     *
     * \pre It must be possible to select the interface in this list
     * \sa canSelectInterface()
     */
    std::optional<size_type> findIndexOfParameterValue(unsigned int value) const noexcept;

    /*! \brief Find the index of given standard
     *
     * Return a valid index if an interface with given \a standard exists,
     * otherwise an object without any index.
     *
     * \note This method can also be called if its not possible to select an interface.
     */
    std::optional<size_type> findIndexOfStandard(InterfaceStandard standard) const noexcept;

    /*! \brief Create an interface list from given vendor identifier and product identifier
     *
     * Returns a list depending on \a vid and \a pid for known ones.
     * For some multi-interface serial adapter, on certain platform,
     * a list, representing a system handled only adapter, can be returned.
     * Otherwise, a default constructed list is returned.
     *
     * \sa systemHandledOnly()
     * \sa isSystemHandledOnly()
     */
    static
    InterfaceList fromVendorIdentifierAndProductIdentifier(quint16 vid, quint16 pid);

    /*! \brief Returns a list that represents a system only handled multi-interface adapter
     *
     * \sa isSystemHandledOnly()
     */
    static
    InterfaceList systemHandledOnly();

    /*! \brief Create an interface list for a Moxa serial port
     *
     * \todo Currently only UPort 1250 is supported
     *
     * \note Returns the adapter specific list regardless of the platform
     */
    static
    InterfaceList fromMoxaProductIdentifier(quint16 pid);

    /*! \brief Create an interface list for a Moxa UPort
     *
     * Returns a list for UPort 1250/1250I/1450/1450I/1650-8/1650-16 series.
     *
     * \note Returns the adapter specific list regardless of the platform
     */
    static
    InterfaceList moxaUPort_1250_1450_1650();

   private:

    InterfaceList(const std::vector<Interface> & list);

    std::vector<Interface> mList;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_INTERFACE_LIST_H
