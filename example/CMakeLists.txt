add_executable(canvas2D_example main.cpp
        Example.cpp
        Example.hpp)

find_package(glfw3 REQUIRED)

target_link_libraries(canvas2D_example
    PRIVATE canvas2D glfw
)

target_include_directories(canvas2D_example PRIVATE
    ${CMAKE_SOURCE_DIR}/canvas2D/include
)
