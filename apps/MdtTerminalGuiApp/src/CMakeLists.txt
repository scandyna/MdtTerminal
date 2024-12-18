
add_executable(mdtterminalguiapp
  ConsoleWidget.cpp
  CentralWidget.cpp
  MainWindow.cpp
  main.cpp
)

target_compile_definitions(mdtterminalguiapp
  PRIVATE
    QT_NO_CAST_DEFINITIONS QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_BYTEARRAY
)

target_link_libraries(mdtterminalguiapp
  PRIVATE
    Qt5::Widgets
    Mdt::SerialPort
    Mdt::SerialPort_Widgets
)

if(BUILD_USE_IPO_LTO)
  set_target_properties(mdtterminalguiapp
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
  )
endif()

target_include_directories(mdtterminalguiapp
  PRIVATE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
