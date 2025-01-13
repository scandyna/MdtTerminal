// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PORT_INFO_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_PORT_INFO_LIST_TABLE_MODEL_H

#include "Mdt/SerialPort/AbstractPortInfoListTableModel.h"
#include "mdt_serialport_export.h"
#include <QSerialPortInfo>
#include <QList>
#include <cassert>

namespace Mdt{ namespace SerialPort{

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

      return mList.at(row);
    }

   private:

    void doFetchAvailablePorts() override;

    QString doGetPortNameAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return mList[row].portName();
    }

    QString doGetSystemLocationAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return mList[row].systemLocation();
    }

    QString doGetDescriptionAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return mList[row].description();
    }

    QString doGetManufacturerAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return mList[row].manufacturer();
    }

    QString doGetSerialNumberAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return mList[row].serialNumber();
    }

    QString doGetVendorIdentifierAtRow(int row) const noexcept override;
    QString doGetProductIdentifierAtRow(int row) const noexcept override;

    int rowCountWithoutParentIndex() const noexcept override
    {
      return mList.size();
    }

    QList<QSerialPortInfo> mList;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PORT_INFO_LIST_TABLE_MODEL_H
