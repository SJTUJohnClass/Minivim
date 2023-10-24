# specify the minimum version of CMake that is supported
cmake_minimum_required(VERSION 3.10)

# include a project name
project(minivim)

# set C++ Version & executable output path
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# make your compiler aware of header directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# find & include ncurses library
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# create a variable which includes needed source files
set(MY_SOURCES
    ${PROJECT_SOURCE_DIR}/src/ncurses_demo.cpp
)

# specify an executable, 
# build from the specified source files
add_executable(minivim ${MY_SOURCES})

# link ncurses library with your executable
target_link_libraries(minivim ${CURSES_LIBRARY})