cmake_minimum_required(VERSION 3.21)
project(slim)

option(SLIM_BUILD_SANDBOX   "Build sandbox for slim"               OFF)
option(SLIM_BUILD_DOCS      "Build documentation for slim"         OFF)
option(SLIM_BUILD_TESTS     "Build tests for slim"                 OFF)
option(SLIM_ENABLE_TOOLS    "Enable tools and sanitizers for slim" OFF)
option(SLIM_ENABLE_COVERAGE "Add coverage options for slim"        OFF)

include("cmake/PreventInSourceBuild.cmake")

if(PROJECT_IS_TOP_LEVEL)
  include("cmake/SymlinkCompileCommands.cmake")
endif()

# Definitions

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_compile_definitions(SLIM_PLATFORM_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_compile_definitions(SLIM_PLATFORM_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  add_compile_definitions(SLIM_PLATFORM_MACOS)
else()
  message(FATAL_ERROR "Unrecognized platform ${CMAKE_SYSTEM_NAME}")
endif()

# Subdirectories

set(SLIM_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/slim")
set(SLIM_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SLIM_SANDBOX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sandbox")
set(SLIM_TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

add_subdirectory(src slim)

if(SLIM_BUILD_SANDBOX)
  add_subdirectory(sandbox)
endif()

if(SLIM_BUILD_DOCS)
  add_subdirectory(docs)
endif()

# Options & tooling

include("cmake/CompilerOptions.cmake")
slim_set_compiler_options(slim sandbox)

if(SLIM_ENABLE_TOOLS)
  include("cmake/Tooling.cmake")
  slim_enable_tooling(slim sandbox)

  include("cmake/Sanitizers.cmake")
  slim_enable_sanitizers(slim sandbox)
endif()

# Testing

if(SLIM_BUILD_TESTS)
  include(CTest) # will set BUILD_TESTING to ON
endif()

if(BUILD_TESTING)
  include(FetchContent)
  add_subdirectory(test)

  if(SLIM_ENABLE_COVERAGE)
    include("cmake/Coverage.cmake")
    slim_enable_coverage(slim)
  endif()
endif()
