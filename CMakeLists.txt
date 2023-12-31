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

add_definitions(-DROOT_SOURCE_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include_directories(semana02)
include_directories(semana03)
include_directories(semana04)
include_directories(semana05)
include_directories(semana06)

add_subdirectory(semana02)
add_subdirectory(semana03)
add_subdirectory(semana04)
add_subdirectory(semana05)
add_subdirectory(semana06)
