#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

#include "Example.hpp"

Example* getExample(GLFWwindow* w) {
    return static_cast<Example *>(glfwGetWindowUserPointer(w));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (const auto p = getExample(window); p != nullptr) {
        p->onResize(glm::ivec2{width,height});
    }
}

void key_callback(GLFWwindow* window, const int key, int, const int action, const int mods) {
    if (const auto p = getExample(window); p != nullptr) {
        p->onKey(key,action,mods);
    }
}

void mouse_button_callback(GLFWwindow* window, const int button, const int action, const int mods) {
    if (const auto p = getExample(window); p != nullptr) {
        p->onKey(button,action,mods);
    }
}

void mouse_pos_callback(GLFWwindow * window, double xpos, double ypos) {
    if (const auto p = getExample(window); p != nullptr) {
        p->onMouse({xpos,ypos});
    }
}

int main(){
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (!canvas2D::OpenGL::init(glfwGetProcAddress)) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    auto example = Example();

    glfwSetWindowUserPointer(window,&example);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_pos_callback);

    while (!glfwWindowShouldClose(window)) {
        example.onDraw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
