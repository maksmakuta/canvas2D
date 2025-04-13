#include <GLFW/glfw3.h>
#include <iostream>

#include "Painting.hpp"
#include "canvas2D/Canvas.hpp"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        std::cout << "Key pressed: " << key << std::endl;
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    std::cout << "Mouse moved to: (" << xpos << ", " << ypos << ")" << std::endl;
}

void framebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
    std::cout << "Window resized to: " << width << "x" << height << std::endl;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    auto painter = Painter();
    auto canvas = canvas2D::Canvas();

    glfwSetWindowUserPointer(window,&painter);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    constexpr auto alpha = 0.35f;
    glClearColor(alpha,alpha,alpha,1);

    while (!glfwWindowShouldClose(window)) {
        painter.onDraw(canvas);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}