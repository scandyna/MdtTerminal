
include(MdtAddTest)


mdt_add_test(
  NAME UsbNumericLimitsTest
  TARGET usbNumericLimitsTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/NumericLimitsTest.cpp
)

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
  NAME LibusbDeviceListTest
  TARGET libusbDeviceListTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/LibusbDeviceListTest.cpp
)

mdt_add_test(
  NAME UsbDeviceDescriptorTest
  TARGET usbDeviceDescriptorTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/DeviceDescriptorTest.cpp
)

mdt_add_test(
  NAME UsbEndpointDescriptorTest
  TARGET usbEndpointDescriptorTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/EndpointDescriptorTest.cpp
)

mdt_add_test(
  NAME UsbInterfaceDescriptorTest
  TARGET usbInterfaceDescriptorTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/InterfaceDescriptorTest.cpp
)

mdt_add_test(
  NAME UsbInterfaceTest
  TARGET usbInterfaceTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/InterfaceTest.cpp
)

mdt_add_test(
  NAME UsbConfigDescriptorTest
  TARGET usbConfigDescriptorTest
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/ConfigDescriptorTest.cpp
)
