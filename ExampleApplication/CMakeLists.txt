cmake_minimum_required(VERSION 3.20)

project(example_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
    main.cpp
    Application.cpp
    Scenes.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    renderer3d
)
