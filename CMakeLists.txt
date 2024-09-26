cmake_minimum_required(VERSION 3.28)

project(octree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER clang++)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/camera.cpp
    src/glad.c
    src/keyboard.cpp
    src/main.cpp
    src/mesh.cpp
    src/model.cpp
    src/mouse.cpp
    src/octree.cpp
    src/screen.cpp
    src/shader.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    glfw
)
