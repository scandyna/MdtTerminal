// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_DIALOG_H
#define MDT_SERIAL_PORT_SETTINGS_DIALOG_H

#include "Mdt/SerialPort/Settings.h"
#include "Mdt/SerialPort/SettingsEditor.h"
#include "mdt_serialport_widgets_export.h"
#include <QString>
#include <QDialog>
#include <QSerialPortInfo>
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

    /*! \brief Set given settings to this editor
     */
    void setSettings(const Settings & settings);

   public Q_SLOTS:

    void showPortInfo(const QSerialPortInfo & portInfo) noexcept;

   private Q_SLOTS:

    void fetchAvailablePorts();

   private:

    void fillAvailablePortSettings() noexcept;

    SettingsEditor mEditor;
    std::unique_ptr<Ui::SettingsDialog> mUi;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_DIALOG_H
