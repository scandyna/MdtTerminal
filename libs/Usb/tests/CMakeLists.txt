
include(MdtAddTest)


mdt_add_test(
  NAME LibusbErrorTest
  TARGET libusbErrorTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/LibusbErrorTest.cpp
)

mdt_add_test(
  NAME LibusbRuntimeErrorTest
  TARGET libusbRuntimeErrorTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/LibusbRuntimeErrorTest.cpp
)

mdt_add_test(
  NAME UsbContextTest
  TARGET usbContextTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/ContextTest.cpp
)

mdt_add_test(
  NAME UsbDeviceDescriptorTest
  TARGET usbDeviceDescriptorTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/DeviceDescriptorTest.cpp
)
