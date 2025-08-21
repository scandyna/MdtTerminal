
include(MdtAddTest)


mdt_add_test(
  NAME SerialPortStringHelpersTest
  TARGET serialPortStringHelpersTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/StringHelpersTest.cpp
)

mdt_add_test(
  NAME BaudRateListTableModelTest
  TARGET baudRateListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/BaudRateListTableModelTest.cpp
)

mdt_add_test(
  NAME BaudRateStringFormatTest
  TARGET baudRateStringFormatTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/BaudRateStringFormatTest.cpp
)

mdt_add_test(
  NAME DataBitsListTableModelTest
  TARGET dataBitsListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/DataBitsListTableModelTest.cpp
)

mdt_add_test(
  NAME ParityStringFormatTest
  TARGET parityStringFormatTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/ParityStringFormatTest.cpp
)

mdt_add_test(
  NAME ParityListTableModelTest
  TARGET parityListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/ParityListTableModelTest.cpp
)

mdt_add_test(
  NAME FlowControlStringFormatTest
  TARGET flowControlStringFormatTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/FlowControlStringFormatTest.cpp
)

mdt_add_test(
  NAME FlowControlListTableModelTest
  TARGET flowControlListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/FlowControlListTableModelTest.cpp
)

mdt_add_test(
  NAME StopBitsListTableModelTest
  TARGET stopBitsListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/StopBitsListTableModelTest.cpp
)

mdt_add_test(
  NAME TestPortInfoListTableModelTest
  TARGET testPortInfoListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PortInfoListTableModelTest.cpp
)

# mdt_add_test(
#   NAME SerialPortInterfaceStringFormatTest
#   TARGET serialPortInterfaceStringFormatTest
#   DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
#   SOURCE_FILES
#     src/InterfaceStringFormatTest.cpp
# )

mdt_add_test(
  NAME SerialPortInterfaceTest
  TARGET serialPortInterfaceTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/InterfaceTest.cpp
)

mdt_add_test(
  NAME SerialPortInterfaceListTest
  TARGET serialPortInterfaceListTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/InterfaceListTest.cpp
)

mdt_add_test(
  NAME SerialPortInterfaceListTableModelTest
  TARGET serialPortInterfaceListTableModelTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/InterfaceListTableModelTest.cpp
)

mdt_add_test(
  NAME SendByteByByteSettingsTest
  TARGET sendByteByByteSettingsTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SendByteByByteSettingsTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsTest
  TARGET serialPortSettingsTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsRawDataTest
  TARGET serialPortSettingsRawDataTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsRawDataTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsValidationTest
  TARGET serialPortSettingsValidationTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsValidationTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsBuilderTest
  TARGET serialPortSettingsBuilderTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsBuilderTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsBuilderErrorTest
  TARGET serialPortSettingsBuilderErrorTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortSettingsBuilderErrorTest.cpp
)

mdt_add_test(
  NAME SerialPortSettingsStringFormatTest
  TARGET serialPortSettingsStringFormatTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SettingsStringFormatTest.cpp
)

mdt_add_test(
  NAME SerialPortAbstractEngineTest
  TARGET serialPortAbstractEngineTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/AbstractEngineTest.cpp
)

mdt_add_test(
  NAME SerialPortSetupTest
  TARGET serialPortSetupTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PortSetupTest.cpp
)

mdt_add_test(
  NAME SerialPortTest
  TARGET serialPortTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/SerialPortTest.cpp
)

mdt_add_test(
  NAME SerialPortUsbVendorIdProductIdTestTest
  TARGET serialPortUsbVendorIdProductIdTestTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/UsbVendorIdProductIdTest.cpp
)

mdt_add_test(
  NAME SerialPortDeviceMoxaUPortTest
  TARGET serialPortDeviceMoxaUPortTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/DeviceMoxaUPortTest.cpp
)

mdt_add_test(
  NAME SerialPortPinoutSignalsTest
  TARGET serialPortPinoutSignalsTest
  DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PinoutSignalsTest.cpp
)

mdt_add_test(
  NAME SerialPortPinoutSignalsEventNotifierTest
  TARGET serialPortPinoutSignalsEventNotifierTest
  DEPENDENCIES Mdt::SerialPort Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PinoutSignalsEventNotifierTest.cpp
)

mdt_add_test(
  NAME SerialPortPinoutSignalsUiControllerTest
  TARGET serialPortPinoutSignalsUiControllerTest
  DEPENDENCIES Mdt::SerialPort Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PinoutSignalsUiControllerTest.cpp
)

mdt_add_test(
  NAME SerialPortPinoutSignalUiStateTimerTest
  TARGET serialPortPinoutSignalUiStateTimerTest
  DEPENDENCIES Mdt::SerialPort Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PinoutSignalUiStateTimerTest.cpp
)

mdt_add_test(
  NAME SerialPortPinoutSignalUiStateStateMachineTest
  TARGET serialPortPinoutSignalUiStateStateMachineTest
  DEPENDENCIES Mdt::SerialPort Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PinoutSignalUiStateStateMachineTest.cpp
)

mdt_add_test(
  NAME SerialPortPinoutSignalUiStateTest
  TARGET serialPortPinoutSignalUiStateTest
  DEPENDENCIES Mdt::SerialPort Mdt::SerialPortTestLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/PinoutSignalUiStateTest.cpp
)


if(UNIX)

  mdt_add_test(
    NAME SerialPortFilesystemHelpersTest_Unix
    TARGET serialPortFilesystemHelpersTest_Unix
    DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
    SOURCE_FILES
      src/FilesystemHelpersTest_Unix.cpp
  )

  mdt_add_test(
    NAME SerialPortHandleTest_Unix
    TARGET serialPortHandleTest_Unix
    DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
    SOURCE_FILES
      src/HandleTest_Unix.cpp
  )

  if(BUILD_USB_SANDBOX)

    mdt_add_test(
      NAME UnixFileStatusTest
      TARGET unixFileStatusTest
      DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
      SOURCE_FILES
        src/UnixFileStatusTest.cpp
    )

    mdt_add_test(
      NAME UnixFileStatusFileTypeTest
      TARGET unixFileStatusFileTypeTest
      DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
      SOURCE_FILES
        src/FileStatusFileTypeTest.cpp
    )

    mdt_add_test(
      NAME UnixUdevContextTest
      TARGET unixUdevContextTest
      DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
      SOURCE_FILES
        src/UnixUdevContextTest.cpp
    )

    mdt_add_test(
      NAME UnixUdevDeviceTest
      TARGET unixUdevDeviceTest
      DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
      SOURCE_FILES
        src/UdevDeviceTest.cpp
    )

    # TODO remove
    # mdt_add_test(
    #   NAME UnixUdevBusDevicePortNumberTest
    #   TARGET unixUdevBusDevicePortNumberTest
    #   DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
    #   SOURCE_FILES
    #     src/UdevBusDevicePortNumberTest.cpp
    # )

    mdt_add_test(
      NAME UnixUdevUsbSerialPortTest
      TARGET unixUdevUsbSerialPortTest
      DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
      SOURCE_FILES
        src/UdevUsbSerialPortTest.cpp
    )

    # TODO: does it work without HW ?
    mdt_add_test(
      NAME SerialPortUnixEngineTest
      TARGET serialPortUnixEngineTest
      DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
      SOURCE_FILES
        src/UnixEngineTest.cpp
    )

  endif()

  # TODO this is just a sandbox and will not work on the CI 
  # target_link_libraries(serialPortUnixEngineTest
  #   PRIVATE
  #     usb-1.0
  # )
  # target_include_directories(serialPortUnixEngineTest
  #   PRIVATE
  #     "/usr/include/libusb-1.0"
  # )

endif()

if(LINUX)

  mdt_add_test(
    NAME SerialPortLinuxMoxaUPortTest
    TARGET serialPortLinuxMoxaUPortTest
    DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
    SOURCE_FILES
      src/LinuxMoxaUPortTest.cpp
  )

endif()

if(WIN32)

  mdt_add_test(
    NAME SerialPortFilesystemHelpersTest_Windows
    TARGET serialPortFilesystemHelpersTest_Windows
    DEPENDENCIES Mdt::SerialPort Mdt::Catch2Main Mdt::Catch2Qt
    SOURCE_FILES
      src/FilesystemHelpersTest_Windows.cpp
  )

endif()
