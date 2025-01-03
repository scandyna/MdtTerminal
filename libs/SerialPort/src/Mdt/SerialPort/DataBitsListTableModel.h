// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_DATA_BITS_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_DATA_BITS_LIST_TABLE_MODEL_H

#include "mdt_serialport_export.h"
#include <Mdt/ItemModel/AbstractTableModel.h>
#include <QSerialPort>
#include <QVariant>

namespace Mdt{ namespace SerialPort{

  /*! \brief Access model to a list of data bits
   */
  class MDT_SERIALPORT_EXPORT DataBitsListTableModel : public Mdt::ItemModel::AbstractTableModel
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    DataBitsListTableModel(QObject *parent = nullptr);

    /*! \brief Find the row of corresponding data bits
     */
    int findRowOfDataBits(QSerialPort::DataBits dataBits) const noexcept;

    /*! \brief Get the data bits for given row
     *
     * \pre \a row must be in valid range for this model
     */
    QSerialPort::DataBits dataBitsAtRow(int row) const noexcept;

   private:

    int rowCountWithoutParentIndex() const noexcept override
    {
      return 4;
    }

    int columnCountWithoutParentIndex() const noexcept override
    {
      return 1;
    }

    QVariant displayRoleData(const QModelIndex & index) const noexcept override;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_DATA_BITS_LIST_TABLE_MODEL_H
