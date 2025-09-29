// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_DIRECT_WRITER_H
#define MDT_SERIAL_PORT_DIRECT_WRITER_H

#include "Mdt/SerialPort/AbstractWriter.h"
#include "mdt_serialport_export.h"
#include <cassert>

namespace Mdt{ namespace SerialPort{

  /*! \internal Direct writer implementation
   *
   * \sa Writer
   */
  class MDT_SERIALPORT_EXPORT DirectWriter : public AbstractWriter
  {
   public:

    explicit
    DirectWriter(QIODevice *device, QObject *parent = nullptr);

    bool isDirectWriter() const noexcept override
    {
      return true;
    }

    qint64 write(const QByteArray & data) override
    {
      QIODevice *d = device();
      assert(d != nullptr);
      assert( d->isOpen() );
      assert( d->isWritable() );

      return d->write(data);
    }
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_DIRECT_WRITER_H
