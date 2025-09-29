// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/Writer.h"
#include <QtTest/QtTest>
#include <QBuffer>
#include <chrono>

#include "Mdt/SerialPort/ByteByByteWriter.h"
using Mdt::SerialPort::TestLib::TestByteByByteWriter;

using namespace Mdt::SerialPort;
using namespace std::chrono_literals;


class WriterTest : public QObject
{
  Q_OBJECT

 private slots:

  // void initTestCase();

  void write_ByteByByte();
  void write_ByteByByte_And_clear();
  void write_ByteByByte_close_open_writeAgain();
};


void WriterTest::write_ByteByByte()
{
  QBuffer buffer;
  Writer writer(&buffer);
  QVERIFY( buffer.open(QBuffer::ReadWrite) );

  writer.setSettings( SendByteByByteSettings::enabledWithInterval(100ms) );

  QCOMPARE( writer.write("ABC"), 3 );
  QVERIFY2( buffer.data().size() < 3 , "the whole data has been written directly" );
  QTRY_COMPARE_WITH_TIMEOUT( buffer.data(), "ABC", 2000 );
  /*
   * Let the system process some more events
   * to check that we terminate the send properly
   */
  QTest::qWait(300);
}

void WriterTest::write_ByteByByte_And_clear()
{
  QBuffer buffer;
  Writer writer(&buffer);
  QVERIFY( buffer.open(QBuffer::ReadWrite) );

  writer.setSettings( SendByteByByteSettings::enabledWithInterval(100ms) );

  QCOMPARE( writer.write("ABC"), 3 );
  /*
   * Let the system send a byte
   */
  QTest::qWait(120);

  writer.clear();

  /*
   * Let the system process some events.
   * We should not have sent more than 2 bytes.
   * lso, not assertion or crash must occure
   */
  QTest::qWait(300);
  QVERIFY( buffer.data().size() < 3 );
}

void WriterTest::write_ByteByByte_close_open_writeAgain()
{
  QBuffer buffer;
  Writer writer(&buffer);
  QVERIFY( buffer.open(QBuffer::ReadWrite) );
  writer.setSettings( SendByteByByteSettings::enabledWithInterval(100ms) );

  QCOMPARE( writer.write("ABC"), 3 );
  /*
   * Let the system send a byte
   */
  QTest::qWait(120);

  buffer.close();
  QVERIFY( buffer.open(QBuffer::ReadWrite) );

  QCOMPARE( writer.write("DE"), 2 );
  QTRY_COMPARE_WITH_TIMEOUT( buffer.data(), "DE", 2000 );
}


QTEST_GUILESS_MAIN(WriterTest)
#include "WriterTest_WithEventLoop.moc"
