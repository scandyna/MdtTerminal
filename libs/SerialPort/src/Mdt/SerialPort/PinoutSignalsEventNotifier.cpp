// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "PinoutSignalsEventNotifier.h"
#include <chrono>
#include <cassert>

using namespace std::chrono_literals;

namespace Mdt{ namespace SerialPort{

PinoutSignalsEventNotifier::PinoutSignalsEventNotifier(QSerialPort *serialPort, QObject *parent)
 : AbstractPinoutSignalsEventNotifier(parent),
   mSerialPort(serialPort)
{
  assert(serialPort != nullptr);
  assert( !mSerialPort.isNull() );

  connect(mSerialPort, &QSerialPort::aboutToClose, this, &PinoutSignalsEventNotifier::setAboutToCloseEvent);
  connect(mSerialPort, &QSerialPort::readyRead, this, &PinoutSignalsEventNotifier::setReadyReadEvent);
  connect(mSerialPort, &QSerialPort::bytesWritten, this, &PinoutSignalsEventNotifier::setBytesWrittenEvent);
  connect(mSerialPort, &QSerialPort::dataTerminalReadyChanged, this, &PinoutSignalsEventNotifier::setDataTerminalReadyChangedEvent);

  connect(&mTimer, &QTimer::timeout, this, &PinoutSignalsEventNotifier::setTimerTimeoutEvent);
  mTimer.setTimerType(Qt::CoarseTimer);
  mTimer.setInterval(20ms);
}

void PinoutSignalsEventNotifier::startTimer()
{
  mTimer.start();
}

bool PinoutSignalsEventNotifier::timerIsActive() const
{
  return mTimer.isActive();
}

void PinoutSignalsEventNotifier::stopTimer()
{
  mTimer.stop();
}

qint64 PinoutSignalsEventNotifier::bytesAvailable() const
{
  assert( !mSerialPort.isNull() );

  return mSerialPort->bytesAvailable();
}

qint64 PinoutSignalsEventNotifier::bytesToWrite() const
{
  assert( !mSerialPort.isNull() );

  return mSerialPort->bytesToWrite();
}

QSerialPort::PinoutSignals PinoutSignalsEventNotifier::readPinoutSignals()
{
  assert( !mSerialPort.isNull() );

  return mSerialPort->pinoutSignals();
}

}} // namespace Mdt{ namespace SerialPort{
