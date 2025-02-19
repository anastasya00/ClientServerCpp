cmake_minimum_required(VERSION 3.22)

project(
    ClientServerCpp
    VERSION 1.0
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(CompileOptions)

enable_testing()

add_subdirectory(external)
add_subdirectory(src)
