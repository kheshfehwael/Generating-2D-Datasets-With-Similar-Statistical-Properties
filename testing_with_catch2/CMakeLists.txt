cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(test_pi LANGUAGES CXX)

# embed library picomp in project test_pi
add_subdirectory(my_lib)

# catch is a header only library for testing
# embed library catch in project test_pi
add_subdirectory(catch)

# create executable with all tests
add_executable(picomp_tests catch_main.cpp catch_tests_picomp.cpp)

# link libraries picomp and catch to executable
target_link_libraries(picomp_tests PRIVATE picomp PRIVATE catch)
