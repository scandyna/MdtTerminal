
include(MdtAddTest)

mdt_add_test(
  NAME BaudRateListTableModelTest
  TARGET baudRateListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/BaudRateListTableModelTest.cpp
)

mdt_add_test(
  NAME BaudRateStringFormatTest
  TARGET baudRateStringFormatTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/BaudRateStringFormatTest.cpp
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
  NAME FlowControlStringFormatTest
  TARGET flowControlStringFormatTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/FlowControlStringFormatTest.cpp
)

mdt_add_test(
  NAME FlowControlListTableModelTest
  TARGET flowControlListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/FlowControlListTableModelTest.cpp
)

mdt_add_test(
  NAME StopBitsListTableModelTest
  TARGET stopBitsListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/StopBitsListTableModelTest.cpp
)

mdt_add_test(
  NAME TestPortInfoListTableModelTest
  TARGET testPortInfoListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PortInfoListTableModelTest.cpp
)

# mdt_add_test(
#   NAME SerialPortInterfaceStringFormatTest
#   TARGET serialPortInterfaceStringFormatTest
#   DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
#   SOURCE_FILES
#     src/InterfaceStringFormatTest.cpp
# )

mdt_add_test(
  NAME SerialPortInterfaceTest
  TARGET serialPortInterfaceTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/InterfaceTest.cpp
)

mdt_add_test(
  NAME SerialPortInterfaceListTest
  TARGET serialPortInterfaceListTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/InterfaceListTest.cpp
)

mdt_add_test(
  NAME SerialPortInterfaceListTableModelTest
  TARGET serialPortInterfaceListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/InterfaceListTableModelTest.cpp
)

mdt_add_test(
  NAME SendByteByByteSettingsTest
  TARGET sendByteByByteSettingsTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SendByteByByteSettingsTest.cpp
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
  NAME SerialPortSettingsStringFormatTest
  TARGET serialPortSettingsStringFormatTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SettingsStringFormatTest.cpp
)

mdt_add_test(
  NAME SerialPortSetupTest
  TARGET serialPortSetupTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PortSetupTest.cpp
)

mdt_add_test(
  NAME SerialPortTest
  TARGET serialPortTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortTest.cpp
)
