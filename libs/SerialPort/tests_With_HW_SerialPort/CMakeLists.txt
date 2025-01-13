
include(MdtAddTest)

mdt_add_test(
  NAME PortInfoListTableModelTest
  TARGET portInfoListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PortInfoListTableModelTest.cpp
)
