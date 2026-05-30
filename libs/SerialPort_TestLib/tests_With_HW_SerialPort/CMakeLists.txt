
include(MdtAddTest)

mdt_add_test(
  NAME SerialPortTestLib_Helpers_With_HW_Test
  TARGET serialPortTestLib_Helpers_With_HW_Test
  DEPENDENCIES Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/HelpersTest.cpp
)

