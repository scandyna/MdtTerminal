// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_DIALOG_H
#define MDT_SERIAL_PORT_SETTINGS_DIALOG_H

#include "mdt_serialport_widgets_export.h"
#include <QString>
#include <QDialog>
#include <QSerialPortInfo>
#include <QList>
#include <memory>

namespace Mdt{ namespace SerialPort{

  namespace Ui{
    class SettingsDialog;
  } // namespace Ui{

  /*! \brief Serial port settings dialog
   */
  class MDT_SERIALPORT_WIDGETS_EXPORT SettingsDialog : public QDialog
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    SettingsDialog(QWidget *parent = nullptr);

    ~SettingsDialog() noexcept;

   private slots:

    void fetchAvailablePorts();
    void showPortInfoForRow(int row) noexcept;

   private:

    void fillAvailablePortSettings() noexcept;
    void fillAvailableBaudRates() noexcept;
    void fillAvailableDataBits() noexcept;
    void fillAvailableParities() noexcept;
    void fillAvailableStopBits() noexcept;
    void fillAvailableFlowControls() noexcept;

    static
    QString formatVid(const QSerialPortInfo & portInfo) noexcept;

    static
    QString formatPid(const QSerialPortInfo & portInfo) noexcept;

    std::unique_ptr<Ui::SettingsDialog> mUi;
    /// \todo We should make a table model to access available ports
    QList<QSerialPortInfo> mAvailablePorts;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_DIALOG_H
