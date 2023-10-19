# Detects whether this is a top-level project
get_directory_property(HAS_PARENT PARENT_DIRECTORY)
if(HAS_PARENT)
  set(FILIB_TOPLEVEL_PROJECT OFF)
else()
  set(FILIB_TOPLEVEL_PROJECT ON)
endif()

# Check required CMake version
set(REQUIRED_CMAKE_VERSION "3.8.0")
if(FILIB_TOPLEVEL_PROJECT)
  cmake_minimum_required(VERSION ${REQUIRED_CMAKE_VERSION})
else()
  # Don't use cmake_minimum_required here to avoid implicitly overriding parent policies
  if(${CMAKE_VERSION} VERSION_LESS ${REQUIRED_CMAKE_VERSION})
    message(FATAL_ERROR "CMake required version to build IPC Toolkit is ${REQUIRED_CMAKE_VERSION}")
  endif()
endif()

# Include user-provided default options if available. We do that before the main
# `project()` so that we can define the C/C++ compilers from the option file.
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/FILibOptions.cmake)
  message(STATUS "Using local options file: ${CMAKE_CURRENT_SOURCE_DIR}/FILibOptions.cmake")
  include(${CMAKE_CURRENT_SOURCE_DIR}/FILibOptions.cmake)
endif()

# Enable ccache if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  option(FILIB_WITH_CCACHE "Enable ccache when building filib" ${FILIB_TOPLEVEL_PROJECT})
else()
  option(FILIB_WITH_CCACHE "Enable ccache when building filib" OFF)
endif()
if(FILIB_WITH_CCACHE AND CCACHE_PROGRAM)
  message(STATUS "Enabling Ccache support (${CCACHE_PROGRAM})")
  set(ccacheEnv
    CCACHE_BASEDIR=${CMAKE_BINARY_DIR}
    CCACHE_SLOPPINESS=clang_index_store,include_file_ctime,include_file_mtime,locale,pch_defines,time_macros
  )
  foreach(lang IN ITEMS C CXX)
    set(CMAKE_${lang}_COMPILER_LAUNCHER
      ${CMAKE_COMMAND} -E env ${ccacheEnv} ${CCACHE_PROGRAM}
    )
  endforeach()
endif()

################################################################################
# CMake Policies
################################################################################

cmake_policy(SET CMP0054 NEW) # Only interpret if() arguments as variables or keywords when unquoted.
cmake_policy(SET CMP0076 NEW) # target_sources() command converts relative paths to absolute.
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24")
  cmake_policy(SET CMP0135 NEW) # Set the timestamps of all extracted contents to the time of the extraction.
endif()

################################################################################

project(filib DESCRIPTION "A fast interval library" LANGUAGES C CXX VERSION 1.2.1)

# Set default minimum C++ standard
if(FILIB_TOPLEVEL_PROJECT)
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

### Configuration
set(FILIB_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(FILIB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Generate position-independent code by default
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

################################################################################
# filib library
################################################################################

# Add an empty library and fill in the list of sources in `src/CMakeLists.txt`.
add_library(filib_filib)
add_library(filib::filib ALIAS filib_filib)

# Add source to filib
add_subdirectory("${FILIB_SOURCE_DIR}")

# Public include directory for filib
target_include_directories(filib_filib PUBLIC "${FILIB_INCLUDE_DIR}")

################################################################################
# Optional Definitions
################################################################################

# For MSVC, do not use the min and max macros.
target_compile_definitions(filib_filib PUBLIC NOMINMAX)

################################################################################
# Dependencies
################################################################################

# Extra warnings (link last for highest priority)
include(filib_warnings)
target_link_libraries(filib_filib PRIVATE filib::warnings)

################################################################################
# Tests
################################################################################

if(FILIB_TOPLEVEL_PROJECT)
  add_subdirectory(tests)
endif()
