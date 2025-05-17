
add_subdirectory(SerialPort)

# TODO: maybe make optional
add_subdirectory(SerialPort_TestLib)
add_subdirectory(SerialPort_Widgets)

if(BUILD_USB_SANDBOX)
  add_subdirectory(Usb)
endif()

if(BUILD_TESTS OR BUILD_BENCHMARKS)
  add_subdirectory(Catch2)
endif()
