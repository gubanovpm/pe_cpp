set(EXEC qt_sample)

if ("${OS_TYPE}" EQUAL "UNKNOWN")
  message(FATAL_ERROR "Unknown type of OS")
else()
  if ("${OS_TYPE}" EQUAL "WINDOWS")
    add_compile_definitions(WINDOWS_SYSTEM)
    add_compile_options(
      "/O2"
    )
  endif()

  if ("${OS_TYPE}" EQUAL "LINUX")
    add_compile_definitions(LINUX_SYSTEM)
    add_compile_options(
      "-Wall"
      "-Wextra"
      "-O2"
    )
  endif()
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(UI_HEADERS
  ${PROJECT_ROOT_DIR}/sources/mainwindow/mainwindow.ui
)

set(HEADERS
  ${PROJECT_ROOT_DIR}/sources/mainwindow/mainwindow.hh
)

set_property(SOURCE ${HEADERS} PROPERTY SKIP_AUTOGEN ON)

set (SOURCES
  ${PROJECT_ROOT_DIR}/sources/main.cc
  ${PROJECT_ROOT_DIR}/sources/mainwindow/mainwindow.cc
)

qt_add_executable(${EXEC} 
  MANUAL_FINALIZATION
  ${RESOURCES}
  ${SOURCES} 
  ${HEADERS} 
  ${UI_HEADERS}
)

include_directories(
    ${PROJECT_ROOT_DIR}/sources/
    ${PROJECT_ROOT_DIR}/include/
)

target_link_libraries(${EXEC} PRIVATE 
  Qt6::Core 
  Qt6::Widgets 
  Qt6::Gui
)
