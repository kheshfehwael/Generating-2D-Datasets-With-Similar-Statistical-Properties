cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(test_pi LANGUAGES CXX)
find_package(OpenMP REQUIRED)
# embed library picomp in project test_pi
add_subdirectory(tools)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF) # disable compiler specific extensions
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# catch is a header only library for testing
# embed library catch in project test_pi
add_subdirectory(catch)

# create executable with all tests
add_executable(picomp_tests catch_main.cpp catch_tests_picomp.cpp)

# link libraries picomp and catch to executable
target_link_libraries(picomp_tests PRIVATE same_stats_tools PRIVATE catch)
