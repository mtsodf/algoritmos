add_library(intersect_detection intersect_detection.cpp data_structures.cpp binary_tree.cpp generate_cases.cpp event.cpp segment.cpp)
# target_link_libraries(intersect_detection graham)

add_subdirectory(tests)

add_executable(semana06 semana06.cpp)
target_link_libraries(semana06 intersect_detection ${Boost_LIBRARIES})
add_test(semana06 semana06)

configure_file(run_experiments.sh run_experiments.sh COPYONLY)