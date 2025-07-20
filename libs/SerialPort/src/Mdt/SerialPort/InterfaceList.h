// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
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
     * Returns a list depending on \a vid and \a pid for known ones,
     * otherwise a default constructed list.
     */
    static
    InterfaceList fromVendorIdentifierAndProductIdentifier(quint16 vid, quint16 pid);

    /*! \brief Create an interface list for a Moxa serial port
     *
     * \todo Currently only UPort 1250 is supported
     */
    static
    InterfaceList fromMoxaProductIdentifier(quint16 pid);

    /*! \brief Create an interface list for a Moxa UPort
     *
     * Returns a list for UPort 1250/1250I/1450/1450I/1650-8/1650-16 series.
     */
    static
    InterfaceList moxaUPort_1250_1450_1650();

   private:

    InterfaceList(const std::vector<Interface> & list);

    std::vector<Interface> mList;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_INTERFACE_LIST_H
