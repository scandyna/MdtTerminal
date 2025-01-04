// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_FLOW_CONTROL_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_FLOW_CONTROL_LIST_TABLE_MODEL_H

#include "mdt_serialport_export.h"
#include <Mdt/ItemModel/AbstractTableModel.h>
#include <QSerialPort>
#include <QVariant>

namespace Mdt{ namespace SerialPort{

  /*! \brief Access model to a list of flow control
   */
  class MDT_SERIALPORT_EXPORT FlowControlListTableModel : public Mdt::ItemModel::AbstractTableModel
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    FlowControlListTableModel(QObject *parent = nullptr);

    /*! \brief Find the row of corresponding flow control
     */
    int findRowOfFlowControl(QSerialPort::FlowControl control) const noexcept;

    /*! \brief Get the flow control at given row
     *
     * \pre \a row must be in valid range for this model
     */
    QSerialPort::FlowControl flowControlAtRow(int row) const noexcept;

   private:

    int rowCountWithoutParentIndex() const noexcept override
    {
      return 3;
    }

    int columnCountWithoutParentIndex() const noexcept override
    {
      return 1;
    }

    QVariant displayRoleData(const QModelIndex & index) const noexcept override;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_FLOW_CONTROL_LIST_TABLE_MODEL_H
