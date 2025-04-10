// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PORT_INFO_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_PORT_INFO_LIST_TABLE_MODEL_H

#include "Mdt/SerialPort/AbstractPortInfoListTableModel.h"
#include <Mdt/ItemModel/StlContiguousContainerAdapter.h>
#include "mdt_serialport_export.h"
#include <QSerialPortInfo>
#include <QList>
#include <cassert>

namespace Mdt{ namespace SerialPort{

  /*! \internal
   *
   * In Qt5, QList uses int as size_type.
   * In Qt6 it will be qsizetype, that will probably be a 64bit int.
   * \sa https://doc.qt.io/qt-6/qttypes.html#qsizetype-typedef
   *
   * We keep using QList, to avoid copies in doFetchAvailablePorts().
   * To be ready for Qt6, use an adapter to have somewhat safe int conversions.
   */
  struct MDT_SERIALPORT_EXPORT PortInfoListTableModelAdapterFunctionMap
  {
    using PortInfoList = QList<QSerialPortInfo>;

    using size_type = PortInfoList::size_type;
    using const_reference = const QSerialPortInfo &;

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

  /*! \brief Access model to a list of port info
   */
  class MDT_SERIALPORT_EXPORT PortInfoListTableModel : public AbstractPortInfoListTableModel
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    PortInfoListTableModel(QObject *parent = nullptr);

    /*! \brief Get the port info at given row
     *
     * \pre \a row must be in range of this model
     */
    const QSerialPortInfo & portInfoAtRow(int row) const noexcept
    {
      assert( rowIndexIsInRange(row) );

      return mList.atRow(row);
    }

   private:

    void doFetchAvailablePorts() override;

    QString doGetPortNameAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );

      return mList.atRow(row).portName();
    }

    QString doGetSystemLocationAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );

      return mList.atRow(row).systemLocation();
    }

    QString doGetDescriptionAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );

      return mList.atRow(row).description();
    }

    QString doGetManufacturerAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );

      return mList.atRow(row).manufacturer();
    }

    QString doGetSerialNumberAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );

      return mList.atRow(row).serialNumber();
    }

    std::optional<quint16> doGetVendorIdentifierAtRow(int row) const noexcept override;
    std::optional<quint16> doGetProductIdentifierAtRow(int row) const noexcept override;

    int rowCountWithoutParentIndex() const noexcept override
    {
      return mList.rowCount();
    }

    Mdt::ItemModel::StlContiguousContainerAdapter<QList<QSerialPortInfo>, PortInfoListTableModelAdapterFunctionMap> mList;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PORT_INFO_LIST_TABLE_MODEL_H
