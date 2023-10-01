add_library(graham graham.cpp)
target_link_libraries(graham jarvis random_points)

add_library(utilities utilities.cpp)


add_executable(main main.cpp)
target_link_libraries(main graham polygon utilities ${Boost_LIBRARIES})

# Copy run_circles script to build directory
configure_file(run_circles.sh run_circles.sh COPYONLY)