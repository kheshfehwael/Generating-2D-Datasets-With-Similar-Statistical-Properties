cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(same_stats_tools LANGUAGES CXX)

# search for OpenMP, REQUIRED -> fatal error if not found
find_package(OpenMP REQUIRED)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF) # disable compiler specific extensions
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# setting flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Ofast -ffast-math -fopenmp -march=native")

# add a library to the project using the specified source files
add_library(same_stats_tools STATIC  same_stats.cpp same_stats.h include/same_stats_tools.h src/distances.cpp src/get_stat_values.cpp src/interface_CSV.cpp src/modify.cpp same_stats.h)

# PUBLIC -> targets that link to this target get that include directory
target_include_directories(same_stats_tools PUBLIC include PRIVATE src)

# link to the imported target provided by the FindOpenMP module
target_link_libraries(same_stats_tools PUBLIC OpenMP::OpenMP_CXX)
