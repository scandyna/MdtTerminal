include(MdtAddTest)


mdt_add_test(
  NAME SerialPortSettingsEditorStateTest
  TARGET serialPortSettingsEditorStateTest
  DEPENDENCIES Mdt::SerialPort_Widgets Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SettingsEditorStateTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsEditorStateChangedSignalSpyTest
  TARGET serialPortSettingsEditorStateChangedSignalSpyTest
  DEPENDENCIES Mdt::SerialPort_Widgets Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SettingsEditorStateChangedSignalSpy.cpp
    src/SettingsEditorStateChangedSignalSpyTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsEditorStateMachineTest
  TARGET serialPortSettingsEditorStateMachineTest
  DEPENDENCIES Mdt::SerialPort_Widgets Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SettingsEditorStateChangedSignalSpy.cpp
    src/SettingsEditorStateMachineTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsEditorTest
  TARGET serialPortSettingsEditorTest
  DEPENDENCIES Mdt::SerialPort_Widgets Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/TestSettingsEditor.cpp
    src/SerialPortSettingsEditorTest.cpp
)

mdt_add_test(
  NAME SerialPortPinoutSignalsWidgetTest
  TARGET serialPortPinoutSignalsWidgetTest
  DEPENDENCIES Mdt::SerialPort_Widgets Mdt::SerialPortTestLib Qt6::Test
  SOURCE_FILES
    src/TestSettingsEditor.cpp
    src/PinoutSignalsWidgetTest.cpp
)

set_tests_properties(SerialPortPinoutSignalsWidgetTest
  PROPERTIES
    DISABLED TRUE
)
