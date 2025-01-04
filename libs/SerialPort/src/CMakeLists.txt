
include(GenerateExportHeader)
include(MdtInstallLibrary)

add_library(Mdt_SerialPort
  Mdt/SerialPort/QRuntimeError.cpp
  Mdt/SerialPort/BaudRateListTableModel.cpp
  Mdt/SerialPort/DataBitsListTableModel.cpp
  Mdt/SerialPort/ParityStringFormat.cpp
  Mdt/SerialPort/ParityListTableModel.cpp
  Mdt/SerialPort/FlowControlStringFormat.cpp
  Mdt/SerialPort/FlowControlListTableModel.cpp
  Mdt/SerialPort/Settings.cpp
  Mdt/SerialPort/SettingsRawData.cpp
  Mdt/SerialPort/SettingsValidationError.cpp
  Mdt/SerialPort/SettingsValidation.cpp
  Mdt/SerialPort/SettingsBuilder.cpp
  Mdt/SerialPort/SerialPort.cpp
)

add_library(Mdt::SerialPort ALIAS Mdt_SerialPort)

if(BUILD_USE_IPO_LTO)
  set_target_properties(Mdt_SerialPort
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
  )
endif()

target_compile_definitions(Mdt_SerialPort
  PRIVATE
    QT_NO_CAST_DEFINITIONS QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_BYTEARRAY
)

target_include_directories(Mdt_SerialPort
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(Mdt_SerialPort
  PUBLIC
    Qt5::Core
    Qt5::SerialPort
    Mdt0::ItemModel
)

generate_export_header(Mdt_SerialPort)

mdt_install_library(
  TARGET Mdt_SerialPort
  RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_FILE_WITHOUT_EXTENSION
  ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_mdt_serialport_export.h"
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME SerialPort
  EXPORT_NAMESPACE Mdt${PROJECT_VERSION_MAJOR}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  INSTALL_IS_UNIX_SYSTEM_WIDE ${MDT_INSTALL_IS_UNIX_SYSTEM_WIDE}
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION_COMPATIBILITY ExactVersion
  RUNTIME_COMPONENT Mdt_SerialPort_Runtime
  DEVELOPMENT_COMPONENT Mdt_SerialPort_Dev
)
