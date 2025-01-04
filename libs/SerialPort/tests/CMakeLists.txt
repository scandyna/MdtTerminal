
include(MdtAddTest)

mdt_add_test(
  NAME BaudRateListTableModelTest
  TARGET baudRateListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/BaudRateListTableModelTest.cpp
)

mdt_add_test(
  NAME DataBitsListTableModelTest
  TARGET dataBitsListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/DataBitsListTableModelTest.cpp
)

mdt_add_test(
  NAME ParityStringFormatTest
  TARGET parityStringFormatTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/ParityStringFormatTest.cpp
)

mdt_add_test(
  NAME ParityListTableModelTest
  TARGET parityListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/ParityListTableModelTest.cpp
)

mdt_add_test(
  NAME FlowControlListTableModelTest
  TARGET flowControlListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/FlowControlListTableModelTest.cpp
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
  NAME SerialPortSettingsValidationTest
  TARGET serialPortSettingsValidationTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsValidationTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsBuilderTest
  TARGET serialPortSettingsBuilderTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsBuilderTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsBuilderErrorTest
  TARGET serialPortSettingsBuilderErrorTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsBuilderErrorTest.cpp
)


mdt_add_test(
  NAME SerialPortTest
  TARGET serialPortTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortTest.cpp
)
