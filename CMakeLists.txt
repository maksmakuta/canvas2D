cmake_minimum_required(VERSION 4.0)
project(canvas2D
        VERSION 1.0.0
        DESCRIPTION "2D rendering library for C++"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
option(CANVAS2D_BUILD_EXAMPLE ON)

add_library(canvas2D SHARED
        include/canvas2D/Canvas.hpp
        include/canvas2D/Path.hpp
        include/canvas2D/Texture.hpp
        include/canvas2D/Font.hpp
        include/canvas2D/Color.hpp
        include/canvas2D/Shader.hpp
        src/Canvas.cpp
        src/Color.cpp
        src/Font.cpp
        src/Path.cpp
        src/Shader.cpp
        src/Texture.cpp)

add_executable(canvas2D_test example/main.cpp example/Painting.hpp example/Painting.cpp)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Sail REQUIRED)

target_link_libraries(canvas2D PRIVATE OpenGL::OpenGL glm::glm Sail-c++)
target_include_directories(canvas2D PRIVATE OpenGL::OpenGL glm::glm Sail-c++)

if(CANVAS2D_BUILD_EXAMPLE)
find_package(glfw3 REQUIRED)

target_include_directories(canvas2D_test PRIVATE include glfw)
target_link_libraries(canvas2D_test PRIVATE canvas2D glfw)
endif ()