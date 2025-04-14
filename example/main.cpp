#include <GLFW/glfw3.h>
#include <iostream>

#include "Painting.hpp"
#include "canvas2D/Canvas.hpp"

Painter* getPainter(GLFWwindow* w) {
    return static_cast<Painter*>(glfwGetWindowUserPointer(w));
}

void keyCallback(GLFWwindow* window, const int key, int, const int action, const int mods) {
    if (const auto p = getPainter(window); p != nullptr) {
        p->onKey(key,action,mods);
    }
}

void cursorPositionCallback(GLFWwindow* window,const double x, const double y) {
    if (const auto p = getPainter(window); p != nullptr) {
        p->onMouse({x,y});
    }
}

void framebufferSizeCallback(GLFWwindow* window, const int w, const int h) {
    if (const auto p = getPainter(window); p != nullptr) {
        p->onResize({w,h});
    }
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
    canvas2D::loadOpenGL(glfwGetProcAddress);
    auto painter = Painter();
    painter.onResize({800,600});
    auto canvas = canvas2D::Canvas();

    glfwSetWindowUserPointer(window,&painter);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    while (!glfwWindowShouldClose(window)) {
        painter.onDraw(canvas);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}