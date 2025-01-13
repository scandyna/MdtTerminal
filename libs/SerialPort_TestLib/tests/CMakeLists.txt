
include(MdtAddTest)

mdt_add_test(
  NAME TestLibPortInfoListTableModelTest
  TARGET testLibPortInfoListTableModelTest
  DEPENDENCIES Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/TestPortInfoListTableModelTest.cpp
)
