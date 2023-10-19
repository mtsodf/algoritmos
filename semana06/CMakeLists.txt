add_library(intersect_detection intersect_detection.cpp data_structures.cpp 
            binary_tree.cpp generate_cases.cpp event.cpp segment.cpp avl_tree.cpp)
# target_link_libraries(intersect_detection graham)

add_subdirectory(tests)

add_executable(semana06 semana06.cpp)
target_link_libraries(semana06 intersect_detection ${Boost_LIBRARIES})

configure_file(run_experiments.sh run_experiments.sh COPYONLY)
configure_file(experiments_detection.sh experiments_detection.sh COPYONLY)

configure_file(plot01.sh plot01.sh COPYONLY)
configure_file(plot_grid.sh plot_grid.sh COPYONLY)
configure_file(plot_random.sh plot_random.sh COPYONLY)
configure_file(plot_big.sh plot_big.sh COPYONLY)
configure_file(plot_nintersects.sh plot_nintersects.sh COPYONLY)