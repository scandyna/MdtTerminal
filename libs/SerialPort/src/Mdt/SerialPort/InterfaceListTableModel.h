// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_INTERFACE_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_INTERFACE_LIST_TABLE_MODEL_H

#include "Mdt/SerialPort/Interface.h"
#include "Mdt/SerialPort/InterfaceList.h"
#include "mdt_serialport_export.h"
#include <Mdt/ItemModel/AbstractTableModel.h>
#include <Mdt/ItemModel/StlContiguousContainerAdapter.h>
#include <QVariant>
#include <optional>
#include <cassert>

namespace Mdt{ namespace SerialPort{

  /*! \internal
   */
  struct MDT_SERIALPORT_EXPORT InterfaceListTableModelAdapterFunctionMap
  {
    using size_type = InterfaceList::size_type;
    using const_reference = const Interface &;

    static
    size_type size(const std::optional<InterfaceList> & list) noexcept
    {
      if( list.has_value() ){
        return list->count();
      }
      return 0;
    }

    static
    const_reference atIndex(const std::optional<InterfaceList> & list, size_type index) noexcept
    {
      assert( list.has_value() );

      return list->interfaceAt(index);
    }
  };

  /*! \brief Access model to list available interfaces of a serial port
   */
  class MDT_SERIALPORT_EXPORT InterfaceListTableModel : public Mdt::ItemModel::AbstractTableModel
  {
    Q_OBJECT

   public:

    /*! \brief Column
     */
    enum class Column
    {
      Name,           /*!< Name of the interface, like RS-232 */
      ParameterValue  /*!< Parameter value of the interface */
    };

    /*! \brief Constructor
     */
    explicit
    InterfaceListTableModel(QObject *parent = nullptr);

    /*! \brief Get the column index of the interface name
     */
    static
    constexpr
    int nameColumn() noexcept
    {
      return static_cast<int>(Column::Name);
    }

    /*! \brief Get the column index of the interface parameter value
     */
    static
    constexpr
    int parameterValueColumn() noexcept
    {
      return static_cast<int>(Column::ParameterValue);
    }

    /*! \brief Set the vendor identifier and product identifier
     *
     * Will populate the list depending on \a vid and \a pid for known ones,
     * otherwise it will be the default one (with only RS-232 interface).
     *
     * If \a vid or \a pid has no value,
     * the interface list will also be the default one (with only RS-232 interface).
     *
     * \sa InterfaceList::fromVendorIdentifierAndProductIdentifier()
     *
     * \note If the count of interfaces does not change, this model will not reset,
     * but dataChanged() will be emitted for each item.
     * This can avoid resetting current row in the views while the list may not have changed.
     */
    void setVendorIdentifierAndProductIdentifier(std::optional<quint16> vid, std::optional<quint16> pid);

    /*! \brief Clear the interface list
     *
     * This can be used when no serial port exists,
     * or no port is selected, for example.
     */
    void clear();

   private:

    int rowCountWithoutParentIndex() const noexcept override
    {
      return mList.rowCount();
    }

    int columnCountWithoutParentIndex() const noexcept override
    {
      return 2;
    }

    QVariant displayRoleData(const QModelIndex & index) const noexcept override;

    Mdt::ItemModel::StlContiguousContainerAdapter<std::optional<InterfaceList>, InterfaceListTableModelAdapterFunctionMap> mList;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_INTERFACE_LIST_TABLE_MODEL_H
