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

#include "Mdt/SerialPort/Settings.h"
#include "Mdt/SerialPort/BaudRateListTableModel.h"
#include "Mdt/SerialPort/DataBitsListTableModel.h"
#include "Mdt/SerialPort/ParityListTableModel.h"
#include "Mdt/SerialPort/FlowControlListTableModel.h"
#include "Mdt/SerialPort/StopBitsListTableModel.h"
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

    /*! \brief Get the parity list table model for the view
     *
     * \warning The returned pointer is only valid as long as this editor is.
     * \post Returns a valid pointer.
     */
    QAbstractTableModel *parityListModelForView() noexcept
    {
      return &mParityListTableModel;
    }

    /*! \brief Get the flow control list table model for the view
     *
     * \warning The returned pointer is only valid as long as this editor is.
     * \post Returns a valid pointer.
     */
    QAbstractTableModel *flowControlListModelForView() noexcept
    {
      return &mFlowControlListTableModel;
    }

    /*! \brief Get the stop bits list table model for the view
     *
     * \warning The returned pointer is only valid as long as this editor is.
     * \post Returns a valid pointer.
     */
    QAbstractTableModel *stopBitsListModelForView() noexcept
    {
      return &mStopBitsListTableModel;
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

    /*! \brief Get the current row in the parity list model
     */
    int parityListCurrentRow() const noexcept
    {
      return mParityListCurrentRow;
    }

    /*! \brief Get the current row in the flow control list model
     */
    int flowControlListCurrentRow() const noexcept
    {
      return mFlowControlListCurrentRow;
    }

    /*! \brief Get the current row in the stop bits list model
     */
    int stopBitsListCurrentRow() const noexcept
    {
      return mStopBitsListCurrentRow;
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

    /*! \brief Set the current row in the parity list model
     */
    void setParityListCurrentRowFromUi(int row) noexcept;

    /*! \brief Set the current row in the flow control list model
     */
    void setFlowControlListCurrentRowFromUi(int row) noexcept;

    /*! \brief Set the current row in the stop bits list model
     */
    void setStopBitsListCurrentRowFromUi(int row) noexcept;

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

    /*! \brief Emitted when the current row in the parity list model changed
     *
     * \note This signal is not emitted by setParityListCurrentRowFromUi()
     */
    void parityListCurrentRowChanged(int row) const;

    /*! \brief Emitted when the current row in the flow control list model changed
     *
     * \note This signal is not emitted by setFlowControlListCurrentRowFromUi()
     */
    void flowControlListCurrentRowChanged(int row) const;

    /*! \brief Emitted when the current row in the stop bits list model changed
     *
     * \note This signal is not emitted by setStopBitsListCurrentRowFromUi()
     */
    void stopBitsListCurrentRowChanged(int row) const;

   private:

    /*! \brief Fetch the available standard baud rates supported by the target platform
     */
    void fetchStandardBaudRates();

    void setCurrentBaudRate(const Settings & settings);
    void setCurrentDataBits(const Settings & settings);
    void setCurrentParity(const Settings & settings);
    void setCurrentFlowControl(const Settings & settings);
    void setCurrentStopBits(const Settings & settings);

    int mBaudRateListCurrentRow = -1;
    int mDataBitsListCurrentRow = 0;
    int mParityListCurrentRow = 0;
    int mFlowControlListCurrentRow = 0;
    int mStopBitsListCurrentRow = 0;
    BaudRateListTableModel mBaudRateListTableModel;
    DataBitsListTableModel mDataBitsListTableModel;
    ParityListTableModel mParityListTableModel;
    FlowControlListTableModel mFlowControlListTableModel;
    StopBitsListTableModel mStopBitsListTableModel;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_SETTINGS_EDITOR_H
