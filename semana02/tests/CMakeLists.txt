add_executable(is_inside_test is_inside_test.cpp)
target_link_libraries(is_inside_test polygon)

add_test(NAME is_inside_test COMMAND "./is_inside_test")