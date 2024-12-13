cmake_minimum_required(VERSION 3.29)
project(Baseball LANGUAGES CXX)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SCAN_FOR_MODULES ON)
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
# Warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# String address sanitizer bug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DISABLE_STRING_ANNOTATION")

# Sanitizers
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

# Coverage/Debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -g -O0")

set(SRC_DIR ".")
add_library(GameState)
target_sources(
    GameState
    PUBLIC FILE_SET
           CXX_MODULES
           FILES
           ${SRC_DIR}/GameState.cpp
           ${SRC_DIR}/Player.cpp
           ${SRC_DIR}/Bases.cpp
           ${SRC_DIR}/action.cpp
)

add_compile_options("--coverage")
add_link_options("--coverage")

add_executable(baseball ${SRC_DIR}/main.cpp)
target_link_libraries(baseball GameState ${Boost_LIBRARIES})
