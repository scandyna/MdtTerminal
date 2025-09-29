// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_BYTE_BY_BYTE_WRITER_H
#define MDT_SERIAL_PORT_TEST_LIB_TEST_BYTE_BY_BYTE_WRITER_H

#include "Mdt/SerialPort/AbstractByteByByteWriter.h"
#include "mdt_serialport_testlib_export.h"

namespace Mdt{ namespace SerialPort{ namespace TestLib{

  /*! \internal Byte by byte writer test implementation
   *
   * \sa ByteByByteWriter
   */
  class MDT_SERIALPORT_TESTLIB_EXPORT TestByteByByteWriter : public AbstractByteByByteWriter
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

#endif // #ifndef MDT_SERIAL_PORT_TEST_LIB_TEST_BYTE_BY_BYTE_WRITER_H
