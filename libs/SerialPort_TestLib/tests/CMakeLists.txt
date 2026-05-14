
include(MdtAddTest)

mdt_add_test(
  NAME TestLibPortInfoTest
  TARGET testLibPortInfoTest
  DEPENDENCIES Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/TestPortInfoTest.cpp
)

mdt_add_test(
  NAME TestLibPortInfoListTableModelTest
  TARGET testLibPortInfoListTableModelTest
  DEPENDENCIES Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/TestPortInfoListTableModelTest.cpp
)

mdt_add_test(
  NAME TestLibTestPinoutSignalsEventNotifierTest
  TARGET testLibTestPinoutSignalsEventNotifierTest
  DEPENDENCIES Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/TestPinoutSignalsEventNotifierTest.cpp
)

mdt_add_test(
  NAME TestLibPinoutSignalUiStateChangedSignalSpyTest
  TARGET testLibPinoutSignalUiStateChangedSignalSpyTest
  DEPENDENCIES Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PinoutSignalUiStateChangedSignalSpyTest.cpp
)

mdt_add_test(
  NAME TestLibTestPinoutSignalsUiControllerTest
  TARGET testLibTestPinoutSignalsUiControllerTest
  DEPENDENCIES Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/TestPinoutSignalsUiControllerTest.cpp
)
