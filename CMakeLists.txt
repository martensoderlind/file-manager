cmake_minimum_required(VERSION 3.10)
project(Library)

include_directories(src)

file(GLOB SOURCES 
    "src/*.cpp" 
    "src/*.h"
)

add_executable(file_manager ${SOURCES})