// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PARITY_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_PARITY_LIST_TABLE_MODEL_H

#include "mdt_serialport_export.h"
#include <Mdt/ItemModel/AbstractTableModel.h>
#include <QSerialPort>
#include <QVariant>

namespace Mdt{ namespace SerialPort{

  /*! \brief Access model to list available parities
   */
  class MDT_SERIALPORT_EXPORT ParityListTableModel : public Mdt::ItemModel::AbstractTableModel
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    ParityListTableModel(QObject *parent = nullptr);

    /*! \brief Find the row of corresponding parity
     */
    int findRowOfParity(QSerialPort::Parity parity) const noexcept;

    /*! \brief Get the parity for given row
     *
     * \pre \a row must be in valid range for this model
     */
    QSerialPort::Parity parityAtRow(int row) const noexcept;

   private:

    int rowCountWithoutParentIndex() const noexcept override
    {
      return 5;
    }

    int columnCountWithoutParentIndex() const noexcept override
    {
      return 1;
    }

    QVariant displayRoleData(const QModelIndex & index) const noexcept override;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PARITY_LIST_TABLE_MODEL_H
