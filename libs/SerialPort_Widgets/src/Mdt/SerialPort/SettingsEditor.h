// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_SETTINGS_EDITOR_H
#define MDT_SERIAL_PORT_SETTINGS_EDITOR_H

#include "Mdt/SerialPort/Settings.h"
#include "Mdt/SerialPort/BaudRateListTableModel.h"
#include "Mdt/SerialPort/DataBitsListTableModel.h"
#include "mdt_serialport_widgets_export.h"
#include <QAbstractTableModel>
#include <QObject>

namespace Mdt{ namespace SerialPort{

  /*! \brief Serial port settings editor
   *
   * \sa SettingsDialog
   */
  class MDT_SERIALPORT_WIDGETS_EXPORT SettingsEditor : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    SettingsEditor(QObject *parent = nullptr);

    /*! \brief Get the baud rate list table model for the view
     *
     * \warning The returned pointer is only valid as long as this editor is.
     * \post Returns a valid pointer.
     */
    QAbstractTableModel *baudRateListModelForView() noexcept
    {
      return &mBaudRateListTableModel;
    }

    /*! \brief Get the data bits list table model for the view
     *
     * \warning The returned pointer is only valid as long as this editor is.
     * \post Returns a valid pointer.
     */
    QAbstractTableModel *dataBitsListModelForView() noexcept
    {
      return &mDataBitsListTableModel;
    }

    /*! \brief Get the current row in the baud rate list model
     */
    int baudRateListCurrentRow() const noexcept
    {
      return mBaudRateListCurrentRow;
    }

    /*! \brief Get the current row in the data bits list model
     */
    int dataBitsListCurrentRow() const noexcept
    {
      return mDataBitsListCurrentRow;
    }

    /*! \brief Fetch available port settings
     */
    void fetchAvailablePortSettings();

    /*! \brief Set given settings to this editor
     */
    void setSettings(const Settings & settings);

   public Q_SLOTS:

    /*! \brief Set the current row in the baud rate list model
     */
    void setBaudRateListCurrentRowFromUi(int row) noexcept;

    /*! \brief Set the current row in the data bits list model
     */
    void setDataBitsListCurrentRowFromUi(int row) noexcept;

   Q_SIGNALS:

    /*! \brief Emitted when the current row in the baud rate list model changed
     *
     * \note This signal is not emitted by setBaudRateListCurrentRowFromUi()
     */
    void baudRateListCurrentRowChanged(int row) const;

    /*! \brief Emitted when the current row in the data bits list model changed
     *
     * \note This signal is not emitted by setDataBitsListCurrentRowFromUi()
     */
    void dataBitsListCurrentRowChanged(int row) const;

   private:

    /*! \brief Fetch the available standard baud rates supported by the target platform
     */
    void fetchStandardBaudRates();

    void setCurrentBaudRate(const Settings & settings);
    void setCurrentDataBits(const Settings & settings);

    int mBaudRateListCurrentRow = -1;
    int mDataBitsListCurrentRow = 0;
    BaudRateListTableModel mBaudRateListTableModel;
    DataBitsListTableModel mDataBitsListTableModel;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_EDITOR_H
