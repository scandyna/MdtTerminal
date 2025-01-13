include(MdtAddTest)


mdt_add_test(
  NAME SerialPortSettingsEditorTest
  TARGET serialPortSettingsEditorTest
  DEPENDENCIES Mdt::SerialPort_Widgets Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/TestSettingsEditor.cpp
    src/SerialPortSettingsEditorTest.cpp
)
