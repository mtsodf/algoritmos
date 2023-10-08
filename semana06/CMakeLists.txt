add_library(intersect_detection intersect_detection.cpp)
target_link_libraries(intersect_detection graham)

add_subdirectory(tests)

add_executable(semana06 semana06.cpp)
target_link_libraries(semana06 intersect_detection ${Boost_LIBRARIES})