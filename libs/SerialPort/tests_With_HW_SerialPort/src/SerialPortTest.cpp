// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/SerialPort.h"
#include "Mdt/SerialPort/TestLib/Helpers.h"
#include <QtTest/QtTest>

using namespace Mdt::SerialPort;
using Mdt::SerialPort::TestLib::findFirstAvailableSerialPort;

class SerialPortTest : public QObject
{
  Q_OBJECT

 private slots:

  void defaultConstructed();
  void openExistingPort_ThenClose();
  void pinoutSignalsEventNotification_OFF();
  void pinoutSignalsEventNotification_ON();
};

void SerialPortTest::defaultConstructed()
{
  SerialPort port;

  QVERIFY( !port.isOpen() );
  QVERIFY( !port.hasRequiredSettings() );
}

void SerialPortTest::openExistingPort_ThenClose()
{
  SerialPort port;

  const auto portInfo = findFirstAvailableSerialPort();
  QVERIFY( portInfo.has_value() );
  const auto settings = Settings::defaultSettingsWithPortInfo(*portInfo);

  port.setSettings(settings);

  port.openReadWrite();
  QVERIFY( port.isOpen() );

  port.close();
  QVERIFY( !port.isOpen() );
}


class PinoutSignalsEventReceiver : public QObject
{
  Q_OBJECT

 public slots:

  void setSignals(const PinoutSignals &)
  {
    ++mPinoutSignalsChangedCount;
  }

  int pinoutSignalsChangedCount() const noexcept
  {
    return mPinoutSignalsChangedCount;
  }

 private:

  int mPinoutSignalsChangedCount = 0;
};


void SerialPortTest::pinoutSignalsEventNotification_OFF()
{
  SerialPort port;
  PinoutSignalsEventReceiver pinoutSignalsEventReceiver;
  connect(&port, &SerialPort::pinoutSignalsChanged, &pinoutSignalsEventReceiver, &PinoutSignalsEventReceiver::setSignals);

  const auto portInfo = findFirstAvailableSerialPort();
  QVERIFY( portInfo.has_value() );
  const auto settings = Settings::defaultSettingsWithPortInfo(*portInfo);
  port.setSettings(settings);

  port.openReadWrite();
  QVERIFY( port.setDataTerminalReady(true) );
  QVERIFY( port.setDataTerminalReady(false) );

  QCOMPARE( pinoutSignalsEventReceiver.pinoutSignalsChangedCount(), 0 );
}

void SerialPortTest::pinoutSignalsEventNotification_ON()
{
  SerialPort port;
  PinoutSignalsEventReceiver pinoutSignalsEventReceiver;
  connect(&port, &SerialPort::pinoutSignalsChanged, &pinoutSignalsEventReceiver, &PinoutSignalsEventReceiver::setSignals);
  port.setPinoutSignalsEventNotifierEnabled(true);

  const auto portInfo = findFirstAvailableSerialPort();
  QVERIFY( portInfo.has_value() );
  const auto settings = Settings::defaultSettingsWithPortInfo(*portInfo);
  port.setSettings(settings);

  port.openReadWrite();
  QVERIFY( port.setDataTerminalReady(true) );
  QVERIFY( port.setDataTerminalReady(false) );

  QVERIFY( pinoutSignalsEventReceiver.pinoutSignalsChangedCount() > 0 );
}


QTEST_GUILESS_MAIN(SerialPortTest)
#include "SerialPortTest.moc"
