cmake_minimum_required(VERSION 3.10)
project(Library)
find_package(Curses REQUIRED)
include_directories(src)
include_directories(src/filemanager)
include_directories(src/menu)

file(GLOB SOURCES 
    "src/*.cpp" 
    "src/*.h"
    "src/filemanager/*.cpp" 
    "src/filemanager/*.h" 
    "src/menu/*.cpp" 
    "src/menu/*.h" 
)

add_executable(file_manager ${SOURCES})
target_link_libraries(file_manager ${CURSES_LIBRARIES})
