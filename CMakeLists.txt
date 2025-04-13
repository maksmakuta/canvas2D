cmake_minimum_required(VERSION 4.0)
project(canvas2D
        VERSION 1.0.0
        DESCRIPTION "2D rendering library for C++"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CANVAS2D_BUILD_EXAMPLE ON)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(SailC++ REQUIRED)

option(SAIL_ASAN "Enable ASAN with supported compilers." ON)
option(OPTION_BUILD_OWN_KHR_HEADERS "" ON)

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

target_link_libraries(canvas2D PUBLIC OpenGL::OpenGL glm::glm SAIL::sail-c++)
target_include_directories(canvas2D PUBLIC OpenGL::OpenGL glm::glm SAIL::sail-c++)

if(CANVAS2D_BUILD_EXAMPLE)
    add_executable(canvas2D_test example/main.cpp example/Painting.hpp example/Painting.cpp)

    find_package(glfw3 REQUIRED)

    target_include_directories(canvas2D_test PUBLIC include glfw)
    target_link_libraries(canvas2D_test PUBLIC canvas2D glfw)
endif ()