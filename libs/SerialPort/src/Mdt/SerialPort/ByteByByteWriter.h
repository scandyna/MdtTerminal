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

#include "Mdt/SerialPort/AbstractByteByByteWriter.h"
#include "mdt_serialport_export.h"
#include <QTimer>
#include <QByteArray>
#include <chrono>

namespace Mdt{ namespace SerialPort{


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

#endif // #ifndef MDT_SERIAL_PORT_BYTE_BY_BYTE_WRITER_H
