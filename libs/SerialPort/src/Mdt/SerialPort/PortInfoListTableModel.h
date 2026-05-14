// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_PORT_INFO_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_PORT_INFO_LIST_TABLE_MODEL_H

#include "Mdt/SerialPort/AbstractPortInfoListTableModel.h"
#include "mdt_serialport_export.h"

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

   private:

    void doFetchAvailablePorts() override;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_PORT_INFO_LIST_TABLE_MODEL_H
