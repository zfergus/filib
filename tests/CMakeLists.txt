### Output directories
if(MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")
endif()

# Enable C++ language for all tests
enable_language(CXX)

add_subdirectory("bisection")
add_subdirectory("comp_exp")
add_subdirectory("fi_test")
add_subdirectory("hornerc")
add_subdirectory("hornercpp")
add_subdirectory("xinewton")
add_subdirectory("comp_sin")