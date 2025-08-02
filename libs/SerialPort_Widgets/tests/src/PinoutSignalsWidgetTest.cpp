// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "Mdt/SerialPort/PinoutSignalsWidget.h"
#include <QtTest/QtTest>


using namespace Mdt::SerialPort;


class PinoutSignalsWidgetTest : public QObject
{
  Q_OBJECT

 public:

    // explicit
    // PinoutSignalsWidgetTest();

 private slots:

  // void initTestCase();

  void sandbox();

};

void PinoutSignalsWidgetTest::sandbox()
{
  PinoutSignalsWidget w;

  w.show();
  /// \todo Should wait properly widget visible

  do{
    QTest::qWait(500);
  }while( w.isVisible() );

  QFAIL("not complete");
}


QTEST_MAIN(PinoutSignalsWidgetTest)
#include "PinoutSignalsWidgetTest.moc"
