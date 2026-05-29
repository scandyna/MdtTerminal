// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PortInfoListTableModel.h"
#include "PortInfoStringFormat.h"
#include <QSerialPortInfo>
#include <cassert>

namespace Mdt{ namespace SerialPort{

PortInfoListTableModel::PortInfoListTableModel(QObject *parent)
 : AbstractPortInfoListTableModel(parent)
{
}

void PortInfoListTableModel::doFetchAvailablePorts()
{
  const auto availablePorts = QSerialPortInfo::availablePorts();
  for(const auto & qPortInfo : availablePorts){
    auto portInfo = PortInfo::fromQSerialPortInfo(qPortInfo);
    if( isExistingSerialPort(portInfo) ){
     addPortInfo(portInfo);
    }
  }
}

}} // namespace Mdt{ namespace SerialPort{
