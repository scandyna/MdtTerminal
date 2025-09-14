
include(MdtAddTest)

mdt_add_test(
  NAME PortInfoListTableModelTest
  TARGET portInfoListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PortInfoListTableModelTest.cpp
)

mdt_add_test(
  NAME SerialPortPortSetup_With_HW_LinuxTest
  TARGET serialPortPortSetup_With_HW_LinuxTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PortSetupLinuxTest.cpp
)

mdt_add_test(
  NAME SerialPortPinoutSignalsEventNotifier_With_HW_Test
  TARGET serialPortPinoutSignalsEventNotifier_With_HW_Test
  DEPENDENCIES Mdt::SerialPort Qt5::Test
  SOURCE_FILES
    src/PinoutSignalsEventNotifierTest.cpp
)
