cmake_minimum_required(VERSION 3.29)
project(Baseball LANGUAGES CXX)
# set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp Bases.cpp Player.cpp GameState.cpp)

add_executable(baseball ${SOURCES})

set_target_properties(baseball PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF)
# target_compile_options(baseball PRIVATE -fmodules-ts -g)
