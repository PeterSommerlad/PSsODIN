cmake_minimum_required(VERSION 3.15)
## not recommended, for testing only, should not be needed with set_cmake_flags=True:
# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILER "g++")
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
##

project(PackageTest CXX)
include_directories("include")


add_executable(example example.cpp)

