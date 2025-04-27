// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_ABSTRACT_SETTINGS_EDITOR_H
#define MDT_SERIAL_PORT_ABSTRACT_SETTINGS_EDITOR_H

#include "Mdt/SerialPort/Settings.h"
#include "Mdt/SerialPort/Interface.h"
#include "Mdt/SerialPort/InterfaceStandard.h"
#include "Mdt/SerialPort/AbstractPortInfoListTableModel.h"
#include "Mdt/SerialPort/BaudRateListTableModel.h"
#include "Mdt/SerialPort/DataBitsListTableModel.h"
#include "Mdt/SerialPort/ParityListTableModel.h"
#include "Mdt/SerialPort/FlowControlListTableModel.h"
#include "Mdt/SerialPort/StopBitsListTableModel.h"
#include "Mdt/SerialPort/InterfaceListTableModel.h"
#include "Mdt/SerialPort/SettingsValidationError.h"
#include "mdt_serialport_widgets_export.h"
#include <QAbstractTableModel>
#include <QSerialPort>
#include <QObject>
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Common base to create serial port settings editor
   */
  class MDT_SERIALPORT_WIDGETS_EXPORT AbstractSettingsEditor : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit
    AbstractSettingsEditor(QObject *parent = nullptr);

    /*! \brief Get the port info list table model for the view
     *
     * \warning The returned pointer is only valid as long as this editor is.
     * \post Returns a valid pointer.
     */
    QAbstractTableModel *portInfoListModelForView() noexcept
    {
      return portInfoListTableModel();
    }

    /*! \brief Get the port name column in the port info list model for the view
     */
    int portNameColumnInPortInfoListModelForView() const noexcept;

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

    /*! \brief Get the interface list table model for the view
     *
     * \warning The returned pointer is only valid as long as this editor is.
     * \post Returns a valid pointer.
     */
    QAbstractTableModel *interfaceListModelForView() noexcept
    {
      return &mInterfaceListTableModel;
    }

    /*! \brief Get the current row in the port info list model
     */
    int portInfoListCurrentRow() const noexcept
    {
      return mPortInfoListCurrentRow;
    }

    /*! \brief Check if a current row has been set for  the port info list
     */
    bool hasPortInfoListCurrentRow() const noexcept
    {
      return mPortInfoListCurrentRow >= 0;
    }

    /*! \brief Get current port name
     *
     * \pre A current port must have been set
     * \sa hasPortInfoListCurrentRow()
     */
    QString currentPortName() const noexcept;

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

    /*! \brief Get the current row in the interface list model
     */
    int interfaceListCurrentRow() const noexcept
    {
      return mInterfaceListCurrentRow;
    }

    /*! \brief Check if sending byte by byte is enabled
     *
     * \sa sendByteByByteIntervalInMilliseconds()
     */
    bool sendByteByByteIsEnabled() const noexcept
    {
      return mSendByteByByteIsEnabled;
    }

    /*! \brief Get the interval between bytes
     *
     * \sa sendByteByByteIsEnabled()
     */
    int sendByteByByteIntervalInMilliseconds() const noexcept
    {
      return mSendByteByByteIntervalInMilliseconds;
    }

    /*! \brief Fetch available ports
     */
    void fetchAvailablePorts();

    /*! \brief Fetch available port settings
     */
    void fetchAvailablePortSettings();

    /*! \brief Set given settings to this editor
     */
    void setSettings(const Settings & settings);

    /*! \brief Build settings with the current state of this editor
     *
     * \exception SettingsValidationError
     * \pre A current port must have been set
     * \sa hasPortInfoListCurrentRow()
     */
    Settings buildSettings() const;

   public Q_SLOTS:

    /*! \brief Set the current row in the port info list model
     */
    void setPortInfoListCurrentRowFromUi(int row) noexcept;

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

    /*! \brief Set the current row in the interface list model
     */
    void setInterfaceListCurrentRowFromUi(int row) noexcept;

    /*! \brief Enable or disable send byte by byte
     */
    void setSendByteByByteEnabledFromUi(bool enabled) noexcept;

    /*! \brief Set the send byte by byte interval in milliseconds
     */
    void setSendByteByByteIntervalInMillisecondsFromUi(int interval) noexcept;

   Q_SIGNALS:

    /*! \brief Emitted when the current row in the port info list model changed
     *
     * \note This signal is not emitted by setPortInfoListCurrentRowFromUi()
     */
    void portInfoListCurrentRowChanged(int row) const;

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

    /*! \brief Emitted when the current row in the interface list model changed
     *
     * \note This signal is not emitted by setInterfaceListCurrentRowFromUi()
     */
    void interfaceListCurrentRowChanged(int row) const;

    /*! \brief Emitted when send byte by byte enabled changed
     *
     * \note This signal is not emitted by setSendByteByByteEnabledFromUi()
     */
    void sendByteByByteIsEnabledChanged(bool enabled) const;

    /*! \brief Emitted when send byte by byte interval changed
     *
     * \note This signal is not emitted by setSendByteByByteIntervalInMillisecondsFromUi()
     */
    void sendByteByByteIntervalInMillisecondsChanged(int interval) const;

   private:

    /*! \brief Fetch the available standard baud rates supported by the target platform
     */
    void fetchStandardBaudRates();

    /*! \brief Fetch some attributes that are specific to the current serial port
     */
    void fetchPortSpecificAttributes();

    void setCurrentPortName(const QString & name);
    void setCurrentBaudRate(const Settings & settings);
    void setCurrentDataBits(const Settings & settings);
    void setCurrentParity(const Settings & settings);
    void setCurrentFlowControl(const Settings & settings);
    void setCurrentStopBits(const Settings & settings);
    void setCurrentInterfaceStandard(InterfaceStandard standard);
    void setSendByteByByteEnabled(bool enabled);
    void setSendByteByByteIntervalInMilliseconds(int interval);

    /// \todo Maybe make public ?
    qint32 currentBaudRate() const noexcept;
    QSerialPort::DataBits currentDataBits() const noexcept;
    QSerialPort::Parity currentParity() const noexcept;
    QSerialPort::FlowControl currentFlowControl() const noexcept;
    QSerialPort::StopBits currentStopBits() const noexcept;
    const Interface & currentInterface() const noexcept;

    bool rowIsMinusOneOrInRangeOfPortInfoList(int row) const noexcept;
    bool rowIsMinusOneOrInRangeOfInterfaceList(int row) const noexcept;

    virtual
    AbstractPortInfoListTableModel *portInfoListTableModel() noexcept = 0;

    virtual
    const AbstractPortInfoListTableModel *constPortInfoListTableModel() const noexcept = 0;

    virtual
    void doFetchAvailablePorts() = 0;

    /*! \brief Notify that the port info changed
     *
     * The concrete implementation should emit a signal
     * with its concrete port info (like QSerialPortInfo).
     *
     * \a row can be < 0 , meaning there is no port info selected
     */
    virtual
    void doNotifyPortInfoChanged(int row) const = 0;

    int mPortInfoListCurrentRow = -1;
    int mBaudRateListCurrentRow = -1;
    int mDataBitsListCurrentRow = 0;
    int mParityListCurrentRow = 0;
    int mFlowControlListCurrentRow = 0;
    int mStopBitsListCurrentRow = 0;
    int mInterfaceListCurrentRow = -1;
    bool mSendByteByByteIsEnabled = false;
    int mSendByteByByteIntervalInMilliseconds = 10;
    BaudRateListTableModel mBaudRateListTableModel;
    DataBitsListTableModel mDataBitsListTableModel;
    ParityListTableModel mParityListTableModel;
    FlowControlListTableModel mFlowControlListTableModel;
    StopBitsListTableModel mStopBitsListTableModel;
    InterfaceListTableModel mInterfaceListTableModel;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ABSTRACT_SETTINGS_EDITOR_H
