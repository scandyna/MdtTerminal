
include(MdtAddTest)

mdt_add_test(
  NAME SerialPortSettingsEditor_With_HW_SerialPort_Test
  TARGET perialPortSettingsEditor_With_HW_SerialPort_Test
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsEditor_With_HW_SerialPort_Test.cpp
)
