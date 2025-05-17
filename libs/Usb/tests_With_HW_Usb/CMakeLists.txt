
include(MdtAddTest)

mdt_add_test(
  NAME UsbSandbox_WithHW_Test
  TARGET usbSandbox_WithHW_Test
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/Sandbox.cpp
)
