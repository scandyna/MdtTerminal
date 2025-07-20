
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
    src/PortPortSetupLinuxTest.cpp
)
