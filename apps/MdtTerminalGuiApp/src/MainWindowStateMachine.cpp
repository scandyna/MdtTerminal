// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtTerminal
 ** Terminal to experiment with some devices using some ports, like serial port.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#include "MainWindowStateMachine.h"
#include <cassert>

MainWindowStateMachine::MainWindowStateMachine(QObject *parent)
 : QObject(parent)
{
}

void MainWindowStateMachine::start()
{
  emit currentStateChanged(mCurrentState);
}

void MainWindowStateMachine::setPortOpenEvent()
{
  if(mCurrentState.enumState() == StateEnum::PortClosed){
    transitFrom_PortClosed_to_PortOpen();
  }
}

void MainWindowStateMachine::setPortClosedEvent()
{
  if(mCurrentState.enumState() == StateEnum::PortOpen){
    transitFrom_PortOpen_to_PortClosed();
  }
}

void MainWindowStateMachine::transitFrom_PortClosed_to_PortOpen()
{
  assert(mCurrentState.enumState() == StateEnum::PortClosed);

  mCurrentState = MainWindowState::portOpen();
  emit currentStateChanged(mCurrentState);
}

void MainWindowStateMachine::transitFrom_PortOpen_to_PortClosed()
{
  assert(mCurrentState.enumState() == StateEnum::PortOpen);

  mCurrentState = MainWindowState::portClosed();
  emit currentStateChanged(mCurrentState);
}
