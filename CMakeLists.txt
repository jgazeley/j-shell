cmake_minimum_required(VERSION 3.13)
project(jshell_host C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

option(ENABLE_CLI "Build with the CLI shell enabled" ON)
if(NOT ENABLE_CLI)
  message(FATAL_ERROR "J-Shell only makes sense with ENABLE_CLI=ON")
endif()

add_executable(jshell
  src/main.c
  src/io_host.c
  src/core.c
  src/menu.c
  src/menu_definitions.c
  src/command.c
  src/plugins.c
  src/plugin_test.c
  src/utils/format.c
)

target_include_directories(jshell PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/cli
)

target_compile_definitions(jshell PRIVATE
  ENABLE_CLI=1
  PLATFORM_HOST=1
)

# Place the .exe into build/
set_target_properties(jshell PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
