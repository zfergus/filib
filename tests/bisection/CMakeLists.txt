get_filename_component(TEST_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_executable(${TEST_NAME}_bin bisection.cpp)
target_link_libraries(${TEST_NAME}_bin PRIVATE filib::filib)