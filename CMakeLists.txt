cmake_minimum_required(VERSION 3.13)

project(
        3D-Render-from-Scratch
        VERSION 1.0 
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(Eigen)

add_executable(
        application
        main.cpp
)

target_link_libraries(
        application
        sfml-graphics
        sfml-window
        sfml-system
)