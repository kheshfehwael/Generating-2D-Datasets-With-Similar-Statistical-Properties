cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(same_stats LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF) # disable compiler specific extensions
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# setting flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Ofast -ffast-math -fopenmp -march=native")

# embed library
add_subdirectory(tools)

# create executable
add_executable(same_stats same_stats.cpp)

target_link_libraries(same_stats PUBLIC same_stats_tools)
