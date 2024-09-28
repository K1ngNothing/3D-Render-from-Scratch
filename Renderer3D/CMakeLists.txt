cmake_minimum_required(VERSION 3.20)

project(renderer3d)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} STATIC
    Camera.cpp
    FrameMovement.cpp
    HVertex.cpp
    Renderer.cpp
    RenderObject.cpp
    Scene.cpp
)

target_sources(${PROJECT_NAME} PUBLIC
    FILE_SET "${PROJECT_NAME}_headers"
    TYPE HEADERS
    BASE_DIRS .
    FILES
        Camera.h
        Renderer.h
        Scene.h)

target_include_directories(${PROJECT_NAME} PUBLIC
    ../Eigen
    ../ #TODO: remove this when settings.h is removed
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
