// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_PORT_INFO_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_TEST_LIB_TEST_PORT_INFO_LIST_TABLE_MODEL_H

#include "Mdt/SerialPort/AbstractPortInfoListTableModel.h"
#include "Mdt/SerialPort/PortInfoStringFormat.h"
#include "Mdt/SerialPort/TestLib/TestPortInfo.h"
#include "mdt_serialport_testlib_export.h"
#include <QString>
#include <QtGlobal>
#include <vector>
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace TestLib{

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
      mAvailablePortList.push_back(port);
    }

    void removeAvailablePort(const TestPortInfo & port);

   private:

    void doFetchAvailablePorts() override
    {
      for(const auto & portInfo : mAvailablePortList){
        addPortInfo(portInfo);
      }
    }

    using PortInfoList = std::vector<TestPortInfo>;

    PortInfoList mAvailablePortList;
  };

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{

#endif // #ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_PORT_INFO_LIST_TABLE_MODEL_H
