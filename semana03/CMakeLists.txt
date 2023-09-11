# Find BOOST
find_package(Boost COMPONENTS program_options REQUIRED)
message(STATUS "Boost found: ${Boost_FOUND}")
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
include_directories(${Boost_INCLUDE_DIRS})


add_library(jarvis jarvis.cpp)
target_link_libraries(jarvis polygon)

add_executable(convex_hull convex_hull_main.cpp)
target_link_libraries(convex_hull polygon jarvis)

#Link boost on convex_hull
target_link_libraries(convex_hull ${Boost_LIBRARIES})

add_test(convex_hull_test convex_hull)

# Copy run_circles script to build directory
configure_file(run_circles.sh run_circles.sh COPYONLY)