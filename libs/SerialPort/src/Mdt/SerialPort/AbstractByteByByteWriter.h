// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_ABSTRACT_BYTE_BY_BYTE_WRITER_H
#define MDT_SERIAL_PORT_ABSTRACT_BYTE_BY_BYTE_WRITER_H

#include "Mdt/SerialPort/AbstractWriter.h"
#include "mdt_serialport_export.h"
#include <QIODevice>
#include <QByteArray>

namespace Mdt{ namespace SerialPort{

  /*! \internal Byte by byte writer implementation base
   *
   * \sa ByteByByteWriter
   */
  class MDT_SERIALPORT_EXPORT AbstractByteByByteWriter : public AbstractWriter
  {
   public:

    explicit
    AbstractByteByByteWriter(QIODevice *device, QObject *parent = nullptr);

    bool isByteByByteWriter() const noexcept override
    {
      return true;
    }

    qint64 write(const QByteArray & data) override;
    void clear() override;

   protected:

    bool hasMoreToSend() const noexcept
    {
      return mSendBufferCurrentIndex < mSendBuffer.size();
    }

   protected Q_SLOTS:

    void setTimerTimeoutEvent();

   private Q_SLOTS:

    void onBytesWritten(qint64 bytes);

   private:

    virtual
    void startTimer() = 0;

    virtual
    void stopTimer() = 0;

    void writeNextByte();

    QByteArray mSendBuffer;
    int mSendBufferCurrentIndex = 0; /// \todo In Qt6, will be qsizetype
  };

}} // namespace Mdt{ namespace SerialPort{

#endif // #ifndef MDT_SERIAL_PORT_ABSTRACT_BYTE_BY_BYTE_WRITER_H
