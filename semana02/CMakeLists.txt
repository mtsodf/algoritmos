add_library(polygon polygon.cpp)
add_executable(triang triang.cpp)
target_link_libraries(triang polygon)

include_directories(./)
add_subdirectory(tests)