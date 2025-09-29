// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/ByteByByteWriter.h"
#include "Mdt/SerialPort/TestLib/TestByteByByteWriter.h"
#include <QtTest/QtTest>
#include <QBuffer>

using namespace Mdt::SerialPort;
using Mdt::SerialPort::TestLib::TestByteByByteWriter;

class ByteByByteWriterTest : public QObject
{
  Q_OBJECT

 private slots:

  // void initTestCase();

  void write_empty();
  void write_once();
  void write_multipleData();
  void clear();
  void close_calls_clear();
};

/*
 * Problem:
 *
 * The implementation of the writer uses the QIODevice::bytesWritten() signal.
 * Without processing some events after a call to QIODevice::write(),
 * the signal will not be emitted.
 *
 * Details:
 *
 * We use QBuffer for the tests.
 * QBuffer::writeData() calls
 * QMetaObject::invokeMethod(this, "_q_emitSignals", Qt::QueuedConnection);
 *
 * This will send a QEvent. _q_emitSignals is invoked as soon as the application enters the event loop.
 * https://doc.qt.io/qt-6/qmetamethod.html#invoke-2
 *
 * In tst_QBuffer::signalTest(),
 * Qt calls some QTestEventLoop::enterLoop(5)
 * (a bit complex and probably not a public API).
 *
 * Here, we simply use qWait().
 */
void processSomeEvents()
{
  QTest::qWait(5);
}


void ByteByByteWriterTest::write_empty()
{
  QBuffer buffer;
  TestByteByByteWriter writer(&buffer);
  QVERIFY( buffer.open(QBuffer::ReadWrite) );

  QCOMPARE( writer.write("") , 0 );
  processSomeEvents();
  QCOMPARE( buffer.data().size() , 0 );
}

void ByteByByteWriterTest::write_once()
{
  QBuffer buffer;
  TestByteByByteWriter writer(&buffer);
  QVERIFY( buffer.open(QBuffer::ReadWrite) );

  QCOMPARE( writer.write("ABC") , 3 );
  processSomeEvents();
  QCOMPARE( buffer.data().size() , 1 );
  QCOMPARE( buffer.data() , "A" );

  QVERIFY( writer.hasMoreToSend() );
  writer.setTimerTimeoutEvent();
  processSomeEvents();
  QCOMPARE( buffer.data() , "AB" );

  QVERIFY( writer.hasMoreToSend() );
  writer.setTimerTimeoutEvent();
  processSomeEvents();
  QCOMPARE( buffer.data() , "ABC" );

  processSomeEvents();
  QVERIFY( !writer.hasMoreToSend() );

  /// \todo also check the special case when timer event still in the event loop
}

void ByteByByteWriterTest::write_multipleData()
{
  QBuffer buffer;
  TestByteByByteWriter writer(&buffer);
  QVERIFY( buffer.open(QBuffer::ReadWrite) );

  QCOMPARE( writer.write("AB") , 2 );
  processSomeEvents();
  QCOMPARE( buffer.data() , "A" );

  QCOMPARE( writer.write("C") , 1 );
  QCOMPARE( buffer.data() , "A" );

  processSomeEvents();
  QVERIFY( writer.hasMoreToSend() );
  writer.setTimerTimeoutEvent();
  QCOMPARE( buffer.data() , "AB" );

  processSomeEvents();
  QVERIFY( writer.hasMoreToSend() );
  writer.setTimerTimeoutEvent();
  QCOMPARE( buffer.data() , "ABC" );

  processSomeEvents();
  QVERIFY( !writer.hasMoreToSend() );
}

void ByteByByteWriterTest::clear()
{
  QBuffer buffer;
  TestByteByByteWriter writer(&buffer);
  QVERIFY( buffer.open(QBuffer::ReadWrite) );

  QCOMPARE( writer.write("ABC") , 3 );
  processSomeEvents();
  QCOMPARE( buffer.data() , "A" );
  QVERIFY( writer.hasMoreToSend() );

  writer.clear();
  processSomeEvents();
  QCOMPARE( buffer.data() , "A" );
  QVERIFY( !writer.hasMoreToSend() );

  /*
   * Emulate the case that a timer event was already placed in the event loop.
   */
  writer.setTimerTimeoutEvent();
  processSomeEvents();
  QCOMPARE( buffer.data() , "A" );
}

void ByteByByteWriterTest::close_calls_clear()
{
  QBuffer buffer;
  TestByteByByteWriter writer(&buffer);
  QVERIFY( buffer.open(QBuffer::ReadWrite) );

  QCOMPARE( writer.write("ABC") , 3 );

  buffer.close();
  processSomeEvents();
  writer.setTimerTimeoutEvent();
  processSomeEvents();

  QVERIFY( buffer.data().size() < 3 );
}

QTEST_GUILESS_MAIN(ByteByByteWriterTest)
#include "ByteByByteWriterTest.moc"
