cmake_minimum_required(VERSION 3.29)
project(Baseball LANGUAGES CXX)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SCAN_FOR_MODULES ON)

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

add_executable(baseball ${SRC_DIR}/main.cpp)
target_link_libraries(baseball GameState)
