add_library(points_triangulation points_triangulation.cpp)
target_link_libraries(points_triangulation polygon random_points graham)



add_executable(semana05 semana05.cpp)
target_link_libraries(semana05 points_triangulation graham polygon utilities ${Boost_LIBRARIES})

add_executable(triangulation_tests triangulation_tests.cpp)
target_link_libraries(triangulation_tests points_triangulation utilities polygon random_points)
add_test(triangulation_tests triangulation_tests)

configure_file(run_circles.sh run_circles.sh COPYONLY)
configure_file(run_shapes.sh run_shapes.sh COPYONLY)