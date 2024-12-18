
include(MdtAddTest)


mdt_add_test(
  NAME SerialPortSettingsTest
  TARGET serialPortSettingsTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SettingsTest.cpp
)

mdt_add_test(
  NAME SerialPortTest
  TARGET serialPortTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortTest.cpp
)
