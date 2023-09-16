add_library(graham graham.cpp)
target_link_libraries(graham jarvis random_points)


add_executable(main main.cpp)
target_link_libraries(main graham)