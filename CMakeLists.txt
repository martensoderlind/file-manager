cmake_minimum_required(VERSION 3.10)
project(Library)

include_directories(src)
include_directories(src/filemanager)

file(GLOB SOURCES 
    "src/*.cpp" 
    "src/*.h"
    "src/filemanager/*.cpp" 
    "src/filemanager/*.h" 
)

add_executable(file_manager ${SOURCES})