
include(MdtAddTest)

mdt_add_test(
  NAME UsbDeviceEnumerator_WithHW_Test
  TARGET usbDeviceEnumerator_WithHW_Test
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/DeviceEnumeratorTest.cpp
)

mdt_add_test(
  NAME LibusbDeviceList_WithHW_Test
  TARGET libusbDeviceList_WithHW_Test
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/LibusbDeviceListTest.cpp
)

mdt_add_test(
  NAME UsbDeviceHandle_WithHW_Test
  TARGET usbDeviceHandle_WithHW_Test
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/DeviceHandleTest.cpp
)

mdt_add_test(
  NAME UsbControlTransfer_WithHW_Test
  TARGET usbControlTransfer_WithHW_Test
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/ControlTransferTest.cpp
)

mdt_add_test(
  NAME UsbSandbox_WithHW_Test
  TARGET usbSandbox_WithHW_Test
  DEPENDENCIES Mdt::Usb Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/Sandbox.cpp
)
