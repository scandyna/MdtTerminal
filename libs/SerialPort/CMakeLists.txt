
add_subdirectory(src)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

if(BUILD_TESTS_WITH_HW_SERIAL_PORT)
  add_subdirectory(tests_With_HW_SerialPort)
endif()

if(BUILD_TESTS_WITH_BRIDGE_PLUG)
  add_subdirectory(tests_WithBridgePlug)
endif()
