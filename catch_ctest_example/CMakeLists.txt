cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(test_pi LANGUAGES CXX)

# embed library picomp in project test_pi
add_subdirectory(my_lib)

# catch is a header only library for testing
# embed library catch in project test_pi
add_subdirectory(catch)

# enable testing
enable_testing()
# create executable with all tests
add_executable(picomp_tests catch_main.cpp catch_tests_picomp.cpp)
# link libraries to executable
target_link_libraries(picomp_tests PRIVATE picomp PRIVATE catch)
# make the executable a test
add_test(NAME PICOMP_TEST COMMAND picomp_tests)