
include(GenerateExportHeader)
include(MdtInstallLibrary)

add_library(Mdt_SerialPort
  Mdt/SerialPort/StringHelpers.cpp
  Mdt/SerialPort/Platform.cpp
  Mdt/SerialPort/QRuntimeError.cpp
  Mdt/SerialPort/FileOpenError.cpp
  Mdt/SerialPort/FilesystemHelpers.cpp
  Mdt/SerialPort/BaudRateStringFormat.cpp
  Mdt/SerialPort/BaudRateListTableModel.cpp
  Mdt/SerialPort/DataBitsListTableModel.cpp
  Mdt/SerialPort/ParityStringFormat.cpp
  Mdt/SerialPort/ParityListTableModel.cpp
  Mdt/SerialPort/FlowControlStringFormat.cpp
  Mdt/SerialPort/FlowControlListTableModel.cpp
  Mdt/SerialPort/StopBitsStringFormat.cpp
  Mdt/SerialPort/StopBitsListTableModel.cpp
  Mdt/SerialPort/PortInfoStringFormat.cpp
  Mdt/SerialPort/AbstractPortInfoListTableModel.cpp
  Mdt/SerialPort/PortInfoListTableModel.cpp
  Mdt/SerialPort/InterfaceStringFormat.cpp
  Mdt/SerialPort/InterfaceStandard.cpp
  Mdt/SerialPort/Interface.cpp
  Mdt/SerialPort/InterfaceList.cpp
  Mdt/SerialPort/InterfaceListTableModel.cpp
  Mdt/SerialPort/SendByteByByteSettings.cpp
  Mdt/SerialPort/Settings.cpp
  Mdt/SerialPort/SettingsRawData.cpp
  Mdt/SerialPort/SettingsValidationError.cpp
  Mdt/SerialPort/SettingsValidation.cpp
  Mdt/SerialPort/SettingsBuilder.cpp
  Mdt/SerialPort/SettingsStringFormat.cpp
  Mdt/SerialPort/UsbVendorIdProductId.cpp
  Mdt/SerialPort/AbstractEngine.cpp
  Mdt/SerialPort/PortSetupError.cpp
  Mdt/SerialPort/PortSetup.cpp
  Mdt/SerialPort/SerialPort.cpp
  Mdt/SerialPort/Device/MoxaUPort.cpp
  Mdt/SerialPort/PinoutSignals.cpp
  Mdt/SerialPort/AbstractPinoutSignalsEventNotifier.cpp
  Mdt/SerialPort/PinoutSignalsEventNotifier.cpp
  Mdt/SerialPort/PinoutSignalUiStateTimer.cpp
  Mdt/SerialPort/PinoutSignalUiStateStateMachine.cpp
  Mdt/SerialPort/PinoutSignalUiState.cpp
  Mdt/SerialPort/AbstractPinoutSignalsUiController.cpp
  Mdt/SerialPort/PinoutSignalsUiController.cpp
  Mdt/SerialPort/AbstractWriter.cpp
  Mdt/SerialPort/DirectWriter.cpp
  Mdt/SerialPort/AbstractByteByByteWriter.cpp
  Mdt/SerialPort/ByteByByteWriter.cpp
  Mdt/SerialPort/Writer.cpp
)

if(UNIX)
  target_sources(Mdt_SerialPort
    PRIVATE
      Mdt/SerialPort/Unix/Handle.cpp
      Mdt/SerialPort/Unix/UnixEngine.cpp
  )
  if(BUILD_USB_SANDBOX)
    target_sources(Mdt_SerialPort
      PRIVATE
        Mdt/SerialPort/Unix/FileStatus.cpp
        Mdt/SerialPort/Unix/FileStatusFileType.cpp
        # Mdt/SerialPort/Unix/UdevBusDevicePortNumber.cpp TODO remove
    )
  endif()
endif()

if(LINUX)
  target_sources(Mdt_SerialPort
    PRIVATE
      Mdt/SerialPort/Linux/MoxaUPort.cpp
      Mdt/SerialPort/PortSetup_Linux.cpp
  )
  if(BUILD_USB_SANDBOX)
    target_sources(Mdt_SerialPort
      PRIVATE
        Mdt/SerialPort/Linux/UdevContext.cpp
        Mdt/SerialPort/Linux/UdevDevice.cpp
        Mdt/SerialPort/Linux/UdevTree.cpp
        Mdt/SerialPort/Linux/UdevUsbSerialPort.cpp
    )
  endif()
endif()


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

if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
  if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 9)
    # https://gitlab.kitware.com/cmake/cmake/-/issues/17834
    target_link_libraries(Mdt_SerialPort
      PUBLIC
        stdc++fs
    )
  endif()
endif()

# TODO: cleanup once Usb is no more a sanbox
# TODO: if want to use Udev, use a target.
#       see https://api.kde.org/ecm/find-module/FindUDev.html
#       and the target conan generates
if(BUILD_USB_SANDBOX)
  target_link_libraries(Mdt_SerialPort
    PUBLIC
      Mdt::Usb
      udev
  )
endif()

generate_export_header(Mdt_SerialPort)

mdt_install_library(
  TARGET Mdt_SerialPort
  RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_FILE_WITHOUT_EXTENSION
  ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_serialport_export.h"
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
