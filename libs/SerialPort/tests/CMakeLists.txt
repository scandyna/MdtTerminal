
include(MdtAddTest)

mdt_add_test(
  NAME BaudRateListTableModelTest
  TARGET baudRateListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/BaudRateListTableModelTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsTest
  TARGET serialPortSettingsTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsRawDataTest
  TARGET serialPortSettingsRawDataTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsRawDataTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsBuilderTest
  TARGET serialPortSettingsBuilderTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsBuilderTest.cpp
)

mdt_add_test(
  NAME SerialPortTest
  TARGET serialPortTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortTest.cpp
)
