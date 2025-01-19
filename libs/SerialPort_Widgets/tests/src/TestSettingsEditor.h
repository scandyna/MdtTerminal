// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2024-2025 Philippe Steinmann.
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

  Mdt::SerialPort::TestLib::TestPortInfo currentPortInfo() const
  {
    return mCurrentPortInfo;
  }

 private:

  QAbstractTableModel *doGetPortInfoListModelForView() noexcept override
  {
    return &mPortInfoListTableModel;
  }

  void doFetchAvailablePorts() override
  {
    mPortInfoListTableModel.fetchAvailablePorts();
  }

  void doNotifyPortInfoChanged(int row) const override;

  Mdt::SerialPort::TestLib::TestPortInfoListTableModel mPortInfoListTableModel;
  mutable Mdt::SerialPort::TestLib::TestPortInfo mCurrentPortInfo;
};

#endif // TEST_SETTINGS_EDITOR_H
