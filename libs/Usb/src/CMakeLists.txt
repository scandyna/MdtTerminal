
include(GenerateExportHeader)
include(MdtInstallLibrary)

add_library(Mdt_Usb
  Mdt/Usb/NumericLimits.cpp
  Mdt/Usb/LibusbError.cpp
  Mdt/Usb/QRuntimeError.cpp
  Mdt/Usb/LibusbRuntimeError.cpp
  Mdt/Usb/Context.cpp
  Mdt/Usb/LibusbDeviceList.cpp
  Mdt/Usb/DeviceEnumerator.cpp
  Mdt/Usb/DeviceDescriptor.cpp
  Mdt/Usb/ConfigDescriptor.cpp
  Mdt/Usb/Interface.cpp
  Mdt/Usb/InterfaceDescriptor.cpp
  Mdt/Usb/EndpointDescriptor.cpp
  Mdt/Usb/DeviceHandle.cpp
)

add_library(Mdt::Usb ALIAS Mdt_Usb)

if(BUILD_USE_IPO_LTO)
  set_target_properties(Mdt_Usb
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
  )
endif()

target_compile_definitions(Mdt_Usb
  PRIVATE
    QT_NO_CAST_DEFINITIONS QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_BYTEARRAY
)

target_include_directories(Mdt_Usb
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(Mdt_Usb
  PUBLIC
    Qt5::Core
)

# TODO This is just for the USB sandbox
# It has to be replaced with a proper target based  target_link_libraries()
# once we have access to conancenter again
target_link_libraries(Mdt_Usb
  PUBLIC
    usb-1.0
)
target_include_directories(Mdt_Usb
  PUBLIC
    "/usr/include/libusb-1.0"
)

# target_link_libraries(Mdt_Usb
#   PUBLIC
#     Qt5::Core
#     Mdt0::ItemModel
# )

generate_export_header(Mdt_Usb)

mdt_install_library(
  TARGET Mdt_Usb
  RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_FILE_WITHOUT_EXTENSION
  ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_usb_export.h"
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME Usb
  EXPORT_NAMESPACE Mdt${PROJECT_VERSION_MAJOR}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  INSTALL_IS_UNIX_SYSTEM_WIDE ${MDT_INSTALL_IS_UNIX_SYSTEM_WIDE}
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION_COMPATIBILITY ExactVersion
  RUNTIME_COMPONENT Mdt_Usb_Runtime
  DEVELOPMENT_COMPONENT Mdt_Usb_Dev
)
