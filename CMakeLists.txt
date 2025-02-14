cmake_minimum_required(VERSION 3.22)

project(
    ThreadedStringHandler
    VERSION 1.0
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(CompileOptions)

add_subdirectory(src)
