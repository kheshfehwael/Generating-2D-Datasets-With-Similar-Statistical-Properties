cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(picomp LANGUAGES CXX)

# search for OpenMP, REQUIRED -> fatal error if not found
find_package(OpenMP REQUIRED)

# add a library to the project using the specified source files
add_library(picomp STATIC include/compute_pi.h src/compute_pi.cpp)

# include directories to use when compiling a given target
target_include_directories(picomp PUBLIC include PRIVATE src)

# link to the imported target provided by the FindOpenMP module
target_link_libraries(picomp PUBLIC OpenMP::OpenMP_CXX)
