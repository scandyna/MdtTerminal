// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "ByteByByteWriter.h"
#include <cassert>

#include <QDebug>

namespace Mdt{ namespace SerialPort{

/*
 * AbstractByteByByteWriter
 */

AbstractByteByByteWriter::AbstractByteByByteWriter(QIODevice *device, QObject *parent)
 : AbstractWriter(device, parent)
{
  assert(device != nullptr);

  connect(device, &QIODevice::bytesWritten, this, &AbstractByteByByteWriter::onBytesWritten);
}

qint64 AbstractByteByByteWriter::write(const QByteArray & data)
{
  QIODevice *d = device();
  assert(d != nullptr);
  assert( d->isOpen() );
  assert( d->isWritable() );

  if( data.isEmpty() ){
    return 0;
  }
  /// \todo remember: we have to add data to our buffer

  /// if hasMoreToSend()

  mSendBuffer = data;
  mSendBufferCurrentIndex = 0;
  writeNextByte();

  return data.size();
}

void AbstractByteByByteWriter::clear()
{
  stopTimer();
  mSendBuffer.clear();
}

void AbstractByteByByteWriter::setTimerTimeoutEvent()
{
  qDebug() << "AbstractByteByByteWriter::setTimerTimeoutEvent()";

  writeNextByte();
}

void AbstractByteByByteWriter::onBytesWritten(qint64 bytes)
{
  qDebug() << "AbstractByteByByteWriter::onBytesWritten() - bytes: " << bytes;

  ++mSendBufferCurrentIndex;
  if( hasMoreToSend() ){
    startTimer();
  }
}

void AbstractByteByByteWriter::writeNextByte()
{
  qDebug() << "AbstractByteByByteWriter::writeNextByte() - current index " << mSendBufferCurrentIndex;

  /*
   * After a call of clear(),
   * it can happen that a timer event was already placed in the event loop,
   * so, despite time stop was called, we are called back with a empty send buffer.
   */
  if( !hasMoreToSend() ){
    return;
  }

  assert( mSendBufferCurrentIndex >= 0 );
  assert( mSendBufferCurrentIndex < mSendBuffer.size() );

  QIODevice *d = device();
  assert(d != nullptr);
  assert( d->isOpen() );

  d->putChar( mSendBuffer[mSendBufferCurrentIndex] );
}

/*
 * ByteByByteWriter
 */

ByteByByteWriter::ByteByByteWriter(QIODevice *device, QObject *parent)
 : AbstractByteByByteWriter(device, parent)
{
  mTimer.setSingleShot(true);
  mTimer.setTimerType(Qt::CoarseTimer); // 5% of the desired interval
  connect(&mTimer, &QTimer::timeout, this, &ByteByByteWriter::setTimerTimeoutEvent);
}

void ByteByByteWriter::setInterval(std::chrono::milliseconds t) noexcept
{
  mTimer.setInterval(t);
}

void ByteByByteWriter::startTimer()
{
  mTimer.start();
}

void ByteByByteWriter::stopTimer()
{
  mTimer.stop();
}

}} // namespace Mdt{ namespace SerialPort{


/*
 * TestByteByByteWriter
 */

namespace Mdt{ namespace SerialPort{ namespace TestLib{

TestByteByByteWriter::TestByteByByteWriter(QIODevice *device, QObject *parent)
 : AbstractByteByByteWriter(device, parent)
{
}

bool TestByteByByteWriter::hasMoreToSend() const noexcept
{
  return AbstractByteByByteWriter::hasMoreToSend();
}

void TestByteByByteWriter::setTimerTimeoutEvent()
{
  AbstractByteByByteWriter::setTimerTimeoutEvent();
}

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{
