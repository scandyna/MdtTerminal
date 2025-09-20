include(MdtAddTest)


mdt_add_test(
  NAME MdtTerminalGuiApp_MainWindowStateTest
  TARGET mdtTerminalGuiApp_MainWindowStateTest
  DEPENDENCIES Mdt::TerminalGuiAppLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/MainWindowStateTest.cpp
)

mdt_add_test(
  NAME MdtTerminalGuiApp_MainWindowStateMachineTest
  TARGET mdtTerminalGuiApp_MainWindowStateMachineTest
  DEPENDENCIES Mdt::TerminalGuiAppLib Mdt::Catch2Main Mdt::Catch2Qt
  SOURCE_FILES
    src/MainWindowStateChangedSignalSpy.cpp
    src/MainWindowStateMachineTest.cpp
)
