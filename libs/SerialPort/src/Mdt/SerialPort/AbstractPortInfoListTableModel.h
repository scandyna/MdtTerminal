// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2024 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_ABSTRACT_PORT_INFO_LIST_TABLE_MODEL_H
#define MDT_SERIAL_PORT_ABSTRACT_PORT_INFO_LIST_TABLE_MODEL_H

#include "mdt_serialport_export.h"
#include <Mdt/ItemModel/AbstractTableModel.h>
#include <QVariant>
#include <QString>

namespace Mdt{ namespace SerialPort{

  /*! \brief Base to implement the access model to a list of port info
   */
  class MDT_SERIALPORT_EXPORT AbstractPortInfoListTableModel : public Mdt::ItemModel::AbstractTableModel
  {
    Q_OBJECT

   public:

    /*! \brief Column
     */
    enum class Column
    {
      PortName = 0,     /*!< Name of the serial port, like ttyS0 on Unix */
      SystemLocation,   /*!< System location of the serial port, like /dev/ttyS0 on Unix */
      Description,      /*!< Description string of the serial port, if available */
      Manufacturer,     /*!< Manufacturer string of the serial port, if available */
      SerialNumber,     /*!< Serial number string of the serial port, if available */
      VendorIdentifier, /*!< Vendor number for the serial port, if available */
      ProductIdentifier /*!< Product number for the serial port, if available */
    };

    /*! \brief Get the column for the port name
     */
    static
    constexpr
    int portNameColumnIndex() noexcept
    {
      return static_cast<int>(Column::PortName);
    }

    /*! \brief Get the column for the system location
     */
    static
    constexpr
    int systemLocationColumnIndex() noexcept
    {
      return static_cast<int>(Column::SystemLocation);
    }

    /*! \brief Get the column for the description
     */
    static
    constexpr
    int descriptionColumnIndex() noexcept
    {
      return static_cast<int>(Column::Description);
    }

    /*! \brief Get the column for the manufacturer
     */
    static
    constexpr
    int manufacturerColumnIndex() noexcept
    {
      return static_cast<int>(Column::Manufacturer);
    }

    /*! \brief Get the column for the serial number
     */
    static
    constexpr
    int serialNumberColumnIndex() noexcept
    {
      return static_cast<int>(Column::SerialNumber);
    }

    /*! \brief Get the column for the vendor identifier
     */
    static
    constexpr
    int vendorIdentifierColumnIndex() noexcept
    {
      return static_cast<int>(Column::VendorIdentifier);
    }

    /*! \brief Get the column for the product identifier
     */
    static
    constexpr
    int productIdentifierColumnIndex() noexcept
    {
      return static_cast<int>(Column::ProductIdentifier);
    }

    /*! \brief Constructor
     */
    explicit
    AbstractPortInfoListTableModel(QObject *parent = nullptr);

    /*! \brief Fetch available ports
     */
    void fetchAvailablePorts();

   private:

    virtual
    void doFetchAvailablePorts() = 0;

    virtual
    QString doGetPortNameAtRow(int row) const noexcept = 0;

    virtual
    QString doGetSystemLocationAtRow(int row) const noexcept = 0;

    virtual
    QString doGetDescriptionAtRow(int row) const noexcept = 0;

    virtual
    QString doGetManufacturerAtRow(int row) const noexcept = 0;

    virtual
    QString doGetSerialNumberAtRow(int row) const noexcept = 0;

    virtual
    QString doGetVendorIdentifierAtRow(int row) const noexcept = 0;

    virtual
    QString doGetProductIdentifierAtRow(int row) const noexcept = 0;

    int columnCountWithoutParentIndex() const noexcept override
    {
      return 7;
    }

    QVariant displayRoleData(const QModelIndex & index) const noexcept override;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ABSTRACT_PORT_INFO_LIST_TABLE_MODEL_H
