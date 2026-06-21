
include(MdtAddTest)


mdt_add_test(
  NAME SerialPort_WithBridgePlug_Test
  TARGET serialPort_WithBridgePlug_Test
  DEPENDENCIES Mdt::SerialPort Mdt::SerialPortTestLib Qt6::Test
  SOURCE_FILES
    src/SerialPortTest.cpp
)
