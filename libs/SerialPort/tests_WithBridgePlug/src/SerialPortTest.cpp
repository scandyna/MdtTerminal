// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2026-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SerialPort.h"
#include "Mdt/SerialPort/TestLib/Helpers.h"
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <chrono>

using namespace Mdt::SerialPort;
using Mdt::SerialPort::TestLib::findSerialPortWithBridgePlug;
using namespace std::chrono_literals;


class SerialPortTest : public QObject
{
  Q_OBJECT

 private slots:

  void writeReadTest();
};


void SerialPortTest::writeReadTest()
{
  SerialPort port;
  QSignalSpy readyReadSpy(&port, &SerialPort::readyRead);
  QVERIFY(readyReadSpy.isValid() );

  const auto portInfo = findSerialPortWithBridgePlug();
  QVERIFY( portInfo.has_value() );
  const auto settings = Settings::defaultSettingsWithPortInfo(*portInfo);
  port.setSettings(settings);
  port.openReadWrite();
  QVERIFY( port.isOpen() );

  QCOMPARE( readyReadSpy.count(), 0 );
  QCOMPARE( port.write("ABCD"), 4 );

/*
 * FIXME Qt BUG: remove pragmas once migrated to Qt6.10+
 * See https://qt-project.atlassian.net/browse/QTBUG-143840
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
  QTRY_VERIFY_WITH_TIMEOUT( readyReadSpy.count() > 0, 5s );
#pragma GCC diagnostic pop
  /*
   * 4 bytes should be transmitted in 1 go
   * keep this test simple, unless it breaks sporadically
   */
  QCOMPARE( port.readAll(), "ABCD" );
}


QTEST_GUILESS_MAIN(SerialPortTest)
#include "SerialPortTest.moc"
