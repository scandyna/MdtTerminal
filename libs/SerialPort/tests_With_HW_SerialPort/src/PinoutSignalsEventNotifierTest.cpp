// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PinoutSignalsEventNotifier.h"
#include <QtTest/QtTest>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <cassert>

using namespace Mdt::SerialPort;


bool openFirstAvailableSerialPort(QSerialPort & serialPort)
{
  assert( !serialPort.isOpen() );

  const auto serialPortInfoList = QSerialPortInfo::availablePorts();
  if( serialPortInfoList.isEmpty() ){
    qDebug() << "could not find any serial port";
    return false;
  }

  serialPort.setPort( serialPortInfoList.at(0) );
  if( !serialPort.open(QSerialPort::ReadOnly) ){
    qDebug() << "open serial port " << serialPort.portName() <<  " failed: " << serialPort.errorString();
    return false;
  }

  return true;
}


class PinoutSignalsEventNotifierTest : public QObject
{
  Q_OBJECT

 public:

    // explicit
    // PinoutSignalsEventNotifierTest();

 private slots:

  // void initTestCase();

  void RTS_changedEvent();
  void DTR_changedEvent();
  void break_changedEvent();
};


void PinoutSignalsEventNotifierTest::RTS_changedEvent()
{
  QSerialPort serialPort;
  PinoutSignalsEventNotifier psn(&serialPort);
  QVERIFY( openFirstAvailableSerialPort(serialPort) );

  QVERIFY( serialPort.setRequestToSend(false) );
  QVERIFY( !psn.currentSignals().requestToSendIsOn() );

  QVERIFY( serialPort.setRequestToSend(true) );
  QVERIFY( psn.currentSignals().requestToSendIsOn() );
}

void PinoutSignalsEventNotifierTest::DTR_changedEvent()
{
  QSerialPort serialPort;
  PinoutSignalsEventNotifier psn(&serialPort);
  QVERIFY( openFirstAvailableSerialPort(serialPort) );

  QVERIFY( serialPort.setDataTerminalReady(false) );
  QVERIFY( !psn.currentSignals().dataTerminalReadyIsOn() );

  QVERIFY( serialPort.setDataTerminalReady(true) );
  QVERIFY( psn.currentSignals().dataTerminalReadyIsOn() );
}

void PinoutSignalsEventNotifierTest::break_changedEvent()
{
  QSerialPort serialPort;
  PinoutSignalsEventNotifier psn(&serialPort);
  QVERIFY( openFirstAvailableSerialPort(serialPort) );

  QVERIFY( serialPort.setBreakEnabled(false) );
  QVERIFY( !psn.currentSignals().breakIsOn() );

  QVERIFY( serialPort.setBreakEnabled(true) );
  QVERIFY( psn.currentSignals().breakIsOn() );

  QVERIFY( serialPort.setBreakEnabled(false) );
}


QTEST_MAIN(PinoutSignalsEventNotifierTest)
#include "PinoutSignalsEventNotifierTest.moc"
