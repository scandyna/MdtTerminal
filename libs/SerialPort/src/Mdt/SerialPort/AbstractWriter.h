// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_ABSTRACT_WRITER_H
#define MDT_SERIAL_PORT_ABSTRACT_WRITER_H

#include "mdt_serialport_export.h"
#include <QObject>
#include <QIODevice>
#include <QPointer>

namespace Mdt{ namespace SerialPort{

  /*! \internal Implementation base for a writer
   *
   * \sa Writer
   */
  class MDT_SERIALPORT_EXPORT AbstractWriter : public QObject
  {
   public:

    explicit
    AbstractWriter(QIODevice *device, QObject *parent = nullptr);

    virtual
    bool isDirectWriter() const noexcept
    {
      return false;
    }

    virtual
    bool isByteByByteWriter() const noexcept
    {
      return false;
    }

    virtual
    qint64 write(const QByteArray & data) = 0;

    virtual
    void clear()
    {
    }

   protected:

    QIODevice *device() const noexcept
    {
      return mDevice;
    }

   private:

    QPointer<QIODevice> mDevice;
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ABSTRACT_WRITER_H
