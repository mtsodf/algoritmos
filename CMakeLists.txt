cmake_minimum_required(VERSION 3.0)
project(Algoritmos)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(semana02)
include_directories(semana02)

add_subdirectory(semana03)
include_directories(semana03)

add_subdirectory(semana04)
