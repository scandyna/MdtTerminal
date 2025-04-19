// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_BAUD_RATE_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_BAUD_RATE_LIST_TABLE_MODEL_H

#include "mdt_serialport_export.h"
#include <Mdt/ItemModel/StlContiguousContainerAdapter.h>
#include <Mdt/ItemModel/AbstractTableModel.h>
#include <QVariant>
#include <QList>
// #include <QtTypes>

namespace Mdt{ namespace SerialPort{

  /*! \internal
   *
   * In Qt5, QList uses int as size_type.
   * In Qt6 it will be qsizetype, that will probably be a 64bit int.
   * \sa https://doc.qt.io/qt-6/qttypes.html#qsizetype-typedef
   *
   * We keep using QList, to avoid copies in fetchStandardBaudRates().
   * To be ready for Qt6, use an adapter to have somewhat safe int conversions.
   */
  struct MDT_SERIALPORT_EXPORT BaudRateListTableModelAdapterFunctionMap
  {
    using BaudRateList = QList<qint32>;

    using size_type = BaudRateList::size_type;
    using const_reference = const qint32 &;

    static
    size_type size(const BaudRateList & list) noexcept
    {
      return list.size();
    }

    static
    const_reference atIndex(const BaudRateList & list, size_type index) noexcept
    {
      return list[index];
    }
  };

  /*! \brief Access model to a list of baud rates
   */
  class MDT_SERIALPORT_EXPORT BaudRateListTableModel : public Mdt::ItemModel::AbstractTableModel
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    BaudRateListTableModel(QObject *parent = nullptr);

    /*! \brief Fetch the available standard baud rates supported by the target platform
     */
    void fetchStandardBaudRates();

    /*! \brief Set a list of baud rates
     */
    void setBaudRateList(const QList<qint32> & list);

    /*! \brief Find the row corresponding to requested baud rate
     *
     * Returns a valid row if requested baud rate exists in the list,
     * or -1 if not found, or the list is empty.
     */
    int findRowOfBaudRate(qint32 baudRate) const noexcept;

   private:

    int rowCountWithoutParentIndex() const noexcept override
    {
      return mList.rowCount();
    }

    int columnCountWithoutParentIndex() const noexcept override
    {
      return 1;
    }

    QVariant displayRoleData(const QModelIndex & index) const noexcept override;

    Mdt::ItemModel::StlContiguousContainerAdapter<QList<qint32>, BaudRateListTableModelAdapterFunctionMap> mList;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_BAUD_RATE_LIST_TABLE_MODEL_H
