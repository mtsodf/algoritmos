add_library(random_points random_points.cpp)

add_library(jarvis jarvis.cpp)
target_link_libraries(jarvis polygon)

add_executable(convex_hull convex_hull_main.cpp)
target_link_libraries(convex_hull polygon jarvis random_points)

#Link boost on convex_hull
target_link_libraries(convex_hull ${Boost_LIBRARIES})


# Copy run_circles script to build directory
configure_file(run_circles.sh run_circles.sh COPYONLY)