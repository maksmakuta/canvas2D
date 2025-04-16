set(OpenGL_GL_PREFERENCE "GLVND")

add_library(canvas2D STATIC
        include/canvas2D/Canvas.hpp

        src/Canvas.cpp
        include/canvas2D/Path.hpp
        include/canvas2D/Image.hpp
        include/canvas2D/Shader.hpp
        include/canvas2D/Color.hpp
        include/canvas2D/Font.hpp
        src/Color.cpp
        src/Font.cpp
        src/Image.cpp
        src/Path.cpp
        src/Shader.cpp
)

target_include_directories(canvas2D PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(canvas2D
        PUBLIC glad tess2 OpenGL::GL glm::glm
)
target_include_directories(canvas2D
        PUBLIC glad tess2 OpenGL::GL glm::glm)