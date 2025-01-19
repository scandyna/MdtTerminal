// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_EDITOR_H
#define MDT_SERIAL_PORT_SETTINGS_EDITOR_H

#include "Mdt/SerialPort/AbstractSettingsEditor.h"
#include "Mdt/SerialPort/PortInfoListTableModel.h"
#include "mdt_serialport_widgets_export.h"
#include <QAbstractTableModel>
#include <QSerialPortInfo>
#include <QObject>

namespace Mdt{ namespace SerialPort{

  /*! \brief Serial port settings editor
   *
   * \sa SettingsDialog
   */
  class MDT_SERIALPORT_WIDGETS_EXPORT SettingsEditor : public AbstractSettingsEditor
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    SettingsEditor(QObject *parent = nullptr);

   Q_SIGNALS:

    /*! \brief Emitted when the current port info changed
     */
    void portInfoChanged(const QSerialPortInfo & portInfo) const;

   private:

    QAbstractTableModel *doGetPortInfoListModelForView() noexcept override
    {
      return &mPortInfoListTableModel;
    }

    void doFetchAvailablePorts() override
    {
      mPortInfoListTableModel.fetchAvailablePorts();
    }

    void doNotifyPortInfoChanged(int row) const override;

    PortInfoListTableModel mPortInfoListTableModel;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_EDITOR_H
