
add_subdirectory(SerialPort)

# TODO: maybe make optional
add_subdirectory(SerialPort_TestLib)
add_subdirectory(SerialPort_Widgets)

if(ENABLE_SERIALPORT_USERSPACE_USB_SUPPORT)
  add_subdirectory(Usb)
endif()

if(BUILD_TESTS OR BUILD_BENCHMARKS)
  add_subdirectory(Catch2)
endif()
