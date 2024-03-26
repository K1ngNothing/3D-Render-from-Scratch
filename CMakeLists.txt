cmake_minimum_required(VERSION 3.20)

project(
    3D-Render-from-Scratch
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(Eigen)
include_directories(src)

add_executable(
    application
    main.cpp
    src/application.cpp
    src/camera.cpp
    src/geometry.cpp
    src/object.cpp
    src/renderer.cpp
    src/world.cpp
)

target_link_libraries(
    application
    sfml-graphics
    sfml-window
    sfml-system
)
