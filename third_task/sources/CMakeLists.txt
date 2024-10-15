set(EXEC polygon)

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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT_DIR}/build)

set(HEADERS
  ${PROJECT_ROOT_DIR}/include/MainWindow.hh
  ${PROJECT_ROOT_DIR}/include/Polygon.hh
  ${PROJECT_ROOT_DIR}/include/RenderArea.hh
  ${PROJECT_ROOT_DIR}/include/Editor.hh
)

set_property(SOURCE ${HEADERS} PROPERTY SKIP_AUTOGEN ON)

set (SOURCES
  ${PROJECT_ROOT_DIR}/sources/main.cc
  ${PROJECT_ROOT_DIR}/sources/MainWindow.cc
  ${PROJECT_ROOT_DIR}/sources/Polygon.cc
  ${PROJECT_ROOT_DIR}/sources/RenderArea.cc
  ${PROJECT_ROOT_DIR}/sources/Editor.cc
)

qt_add_executable(${EXEC} 
  MANUAL_FINALIZATION
  ${SOURCES} 
  ${HEADERS} 
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
