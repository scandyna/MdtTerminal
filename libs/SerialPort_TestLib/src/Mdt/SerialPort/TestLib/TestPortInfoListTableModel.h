// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_PORT_INFO_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_TEST_LIB_TEST_PORT_INFO_LIST_TABLE_MODEL_H

#include "Mdt/SerialPort/AbstractPortInfoListTableModel.h"
#include "Mdt/SerialPort/PortInfoStringFormat.h"
#include "mdt_serialport_testlib_export.h"
#include <QString>
#include <QtGlobal>
#include <QVector>
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace TestLib{

  /*! \brief Data struct for TestPortInfoListTableModel
   */
  struct MDT_SERIALPORT_TESTLIB_EXPORT TestPortInfo
  {
    QString portName;
    QString systemLocation;
    QString description;
    QString manufacturer;
    QString serialNumber;
    quint16 vid = 0;
    quint16 pid = 0;
  };

  /*! \brief Port info list access model for tests
   */
  class MDT_SERIALPORT_TESTLIB_EXPORT TestPortInfoListTableModel : public Mdt::SerialPort::AbstractPortInfoListTableModel
  {
    Q_OBJECT

  public:

    explicit
    TestPortInfoListTableModel(QObject *parent = nullptr);

    void addAvailablePort(const TestPortInfo & port)
    {
      mAvailablePortList.append(port);
    }

    const TestPortInfo & portInfoAtRow(int row) const noexcept;

  private:

    void doFetchAvailablePorts() override
    {
      mList = mAvailablePortList;
    }

    QString doGetPortNameAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return mList[row].portName;
    }

    QString doGetSystemLocationAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return mList[row].systemLocation;
    }

    QString doGetDescriptionAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return mList[row].description;
    }

    QString doGetManufacturerAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return mList[row].manufacturer;
    }

    QString doGetSerialNumberAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return mList[row].serialNumber;
    }

    QString doGetVendorIdentifierAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return Mdt::SerialPort::PortInfoStringFormat::vendorIdentifierToString(mList[row].vid);
    }

    QString doGetProductIdentifierAtRow(int row) const noexcept override
    {
      assert( rowIndexIsInRange(row) );
      return Mdt::SerialPort::PortInfoStringFormat::productIdentifierToString(mList[row].pid);
    }

    int rowCountWithoutParentIndex() const noexcept override
    {
      return mList.size();
    }

    QVector<TestPortInfo> mList;
    QVector<TestPortInfo> mAvailablePortList;
  };

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{

#endif // #ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_PORT_INFO_LIST_TABLE_MODEL_H
