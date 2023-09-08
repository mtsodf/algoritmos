add_library(jarvis jarvis.cpp)
target_link_libraries(jarvis polygon)

add_executable(convex_hull convex_hull_main.cpp)
target_link_libraries(convex_hull polygon jarvis)


add_test(convex_hull_test convex_hull)