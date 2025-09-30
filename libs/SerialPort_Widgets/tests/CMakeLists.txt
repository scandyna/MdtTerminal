include(MdtAddTest)


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
  DEPENDENCIES Mdt::SerialPort_Widgets Mdt::SerialPortTestLib Qt5::Test
  SOURCE_FILES
    src/TestSettingsEditor.cpp
    src/PinoutSignalsWidgetTest.cpp
)

set_tests_properties(SerialPortPinoutSignalsWidgetTest
  PROPERTIES
    DISABLED TRUE
)
