add_executable(is_inside_test is_inside_test.cpp)
target_link_libraries(is_inside_test polygon)
add_test(NAME is_inside_test COMMAND "./is_inside_test")

add_executable(semi_polygon_test semi_polygon_test.cpp)
target_link_libraries(semi_polygon_test polygon)
add_test(NAME semi_polygon_test COMMAND "./semi_polygon_test")

add_executable(triangulate_test triangulate_test.cpp)
target_link_libraries(triangulate_test polygon)
add_test(NAME triangulate_test COMMAND "./triangulate_test")