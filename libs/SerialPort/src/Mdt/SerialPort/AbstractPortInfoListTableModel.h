// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_ABSTRACT_PORT_INFO_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_ABSTRACT_PORT_INFO_LIST_TABLE_MODEL_H

#include "Mdt/SerialPort/PortInfo.h"
#include "mdt_serialport_export.h"
#include <Mdt/ItemModel/StlContiguousContainerAdapter.h>
#include <Mdt/ItemModel/AbstractTableModel.h>
#include <QVariant>
#include <QString>
#include <QtGlobal>
#include <optional>
#include <vector>

namespace Mdt{ namespace SerialPort{

  /*! \brief Serialport port list sorting
   */
  enum class PortListSorting
  {
    None,       /*!< Keep the list of ports as returned by the system */
    ByPortName  /*!< Sort the list of ports by their names  */
  };

  /*! \internal
   */
  struct MDT_SERIALPORT_EXPORT PortInfoListTableModelAdapterFunctionMap
  {
    using PortInfoList = std::vector<PortInfo>;

    using size_type = PortInfoList::size_type;
    using const_reference = const PortInfo &;

    static
    size_type size(const PortInfoList & list) noexcept
    {
      return list.size();
    }

    static
    const_reference atIndex(const PortInfoList & list, size_type index) noexcept
    {
      return list[index];
    }
  };

  /*! \brief Base to implement the access model to a list of port info
   */
  class MDT_SERIALPORT_EXPORT AbstractPortInfoListTableModel : public Mdt::ItemModel::AbstractTableModel
  {
    Q_OBJECT

   public:

    /*! \brief Column
     */
    enum class Column
    {
      PortName = 0,     /*!< Name of the serial port, like ttyS0 on Unix */
      SystemLocation,   /*!< System location of the serial port, like /dev/ttyS0 on Unix */
      Description,      /*!< Description string of the serial port, if available */
      Manufacturer,     /*!< Manufacturer string of the serial port, if available */
      SerialNumber,     /*!< Serial number string of the serial port, if available */
      VendorIdentifier, /*!< Vendor number for the serial port, if available */
      ProductIdentifier /*!< Product number for the serial port, if available */
    };

    /*! \brief Get the column for the port name
     */
    static
    constexpr
    int portNameColumnIndex() noexcept
    {
      return static_cast<int>(Column::PortName);
    }

    /*! \brief Get the column for the system location
     */
    static
    constexpr
    int systemLocationColumnIndex() noexcept
    {
      return static_cast<int>(Column::SystemLocation);
    }

    /*! \brief Get the column for the description
     */
    static
    constexpr
    int descriptionColumnIndex() noexcept
    {
      return static_cast<int>(Column::Description);
    }

    /*! \brief Get the column for the manufacturer
     */
    static
    constexpr
    int manufacturerColumnIndex() noexcept
    {
      return static_cast<int>(Column::Manufacturer);
    }

    /*! \brief Get the column for the serial number
     */
    static
    constexpr
    int serialNumberColumnIndex() noexcept
    {
      return static_cast<int>(Column::SerialNumber);
    }

    /*! \brief Get the column for the vendor identifier
     */
    static
    constexpr
    int vendorIdentifierColumnIndex() noexcept
    {
      return static_cast<int>(Column::VendorIdentifier);
    }

    /*! \brief Get the column for the product identifier
     */
    static
    constexpr
    int productIdentifierColumnIndex() noexcept
    {
      return static_cast<int>(Column::ProductIdentifier);
    }

    /*! \brief Constructor
     */
    explicit
    AbstractPortInfoListTableModel(QObject *parent = nullptr);

    /*! \brief Fetch available ports
     */
    void fetchAvailablePorts(PortListSorting sorting);

    /*! \brief Get the port info at given row
     *
     * \pre \a row must be in range of this model
     */
    const PortInfo & portInfoAtRow(int row) const noexcept
    {
      assert( rowIndexIsInRange(row) );

      return mList.atRow(row);
    }

    /*! \brief Get the port name at given row
     *
     * \pre \a row must be in range of this model
     */
    QString portNameAtRow(int row) const noexcept;

    /*! \brief Find the row of given port name
     *
     * Returns a valid row if requested port name exists in the list,
     * or -1 if not found, or the list is empty.
     */
    int findRowOfPortName(const QString & name) const noexcept;

   protected:

    /*! \brief Add a port info
     *
     * \pre \a portInfo must not be null
     * \sa doFetchAvailablePorts()
     */
    void addPortInfo(const PortInfo & portInfo) noexcept;

   private:

    /*! \brief Fetch available ports
     *
     * The implementation should call addPortInfo()
     * for every fetched port.
     */
    virtual
    void doFetchAvailablePorts() = 0;

    int columnCountWithoutParentIndex() const noexcept override
    {
      return 7;
    }

    int rowCountWithoutParentIndex() const noexcept override
    {
      return mList.rowCount();
    }

    QVariant displayRoleData(const QModelIndex & index) const noexcept override;

    using PortInfoList = std::vector<PortInfo>;
    Mdt::ItemModel::StlContiguousContainerAdapter<PortInfoList, PortInfoListTableModelAdapterFunctionMap> mList;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ABSTRACT_PORT_INFO_LIST_TABLE_MODEL_H
