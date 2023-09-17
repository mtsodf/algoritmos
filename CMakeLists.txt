cmake_minimum_required(VERSION 3.0)
project(Algoritmos)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find BOOST
find_package(Boost COMPONENTS program_options REQUIRED)
message(STATUS "Boost found: ${Boost_FOUND}")
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()
add_subdirectory(semana02)
include_directories(semana02)

add_subdirectory(semana03)
include_directories(semana03)

add_subdirectory(semana04)
