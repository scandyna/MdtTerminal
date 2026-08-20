// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2026 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef TEST_SETTINGS_EDITOR_H
#define TEST_SETTINGS_EDITOR_H

#include "Mdt/SerialPort/AbstractSettingsEditor.h"
#include "Mdt/SerialPort/TestLib/TestPortInfoListTableModel.h"

class TestSettingsEditor : public Mdt::SerialPort::AbstractSettingsEditor
{
  Q_OBJECT

 public:

  /*! \brief Constructor
   */
  explicit
  TestSettingsEditor(QObject *parent = nullptr);

  void addAvailablePort(const Mdt::SerialPort::TestLib::TestPortInfo & port)
  {
    mPortInfoListTableModel.addAvailablePort(port);
  }

  void removeAvailablePort(const Mdt::SerialPort::TestLib::TestPortInfo & port);

  const Mdt::SerialPort::SettingsEditorStateMachine & stateMachine() const noexcept
  {
    return AbstractSettingsEditor::stateMachine();
  }

 private:

  Mdt::SerialPort::AbstractPortInfoListTableModel *portInfoListTableModel() noexcept override
  {
    return &mPortInfoListTableModel;
  }

  const Mdt::SerialPort::AbstractPortInfoListTableModel *constPortInfoListTableModel() const noexcept override
  {
    return &mPortInfoListTableModel;
  }

  void doFetchAvailablePorts() override
  {
    mPortInfoListTableModel.fetchAvailablePorts(Mdt::SerialPort::PortListSorting::None);
  }

  Mdt::SerialPort::TestLib::TestPortInfoListTableModel mPortInfoListTableModel;
};

#endif // TEST_SETTINGS_EDITOR_H
