
add_subdirectory(src)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

if(BUILD_TESTS_WITH_HW_USB)
  add_subdirectory(tests_With_HW_Usb)
endif()
