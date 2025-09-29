// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_BYTE_BY_BYTE_WRITER_H
#define MDT_SERIAL_PORT_BYTE_BY_BYTE_WRITER_H

#include "Mdt/SerialPort/AbstractWriter.h"
#include "mdt_serialport_export.h"
#include <QTimer>
#include <QByteArray>
#include <chrono>

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
    int mSendBufferCurrentIndex = -1; /// \todo In Qt6, will be qsizetype
  };

  /*! \internal Byte by byte writer implementation
   *
   * \sa Writer
   */
  class MDT_SERIALPORT_EXPORT ByteByByteWriter : public AbstractByteByByteWriter
  {
   public:

    explicit
    ByteByByteWriter(QIODevice *device, QObject *parent = nullptr);

    void setInterval(std::chrono::milliseconds t) noexcept;

    int rawIntervalInMilliseconds() const noexcept
    {
      return mTimer.interval();
    }

   private:

    void startTimer() override;
    void stopTimer() override;

    QTimer mTimer;
  };

}} // namespace Mdt{ namespace SerialPort{

namespace Mdt{ namespace SerialPort{ namespace TestLib{

  /*! \internal Byte by byte writer test implementation
   *
   * \sa ByteByByteWriter
   */
  class MDT_SERIALPORT_EXPORT TestByteByByteWriter : public AbstractByteByByteWriter
  {
   public:

    explicit
    TestByteByByteWriter(QIODevice *device, QObject *parent = nullptr);

    bool hasMoreToSend() const noexcept;
    void setTimerTimeoutEvent();

   private:

    void startTimer() override
    {
    }

    void stopTimer() override
    {
    }

  };

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{

#endif // #ifndef MDT_SERIAL_PORT_BYTE_BY_BYTE_WRITER_H
