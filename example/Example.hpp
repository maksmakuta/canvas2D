#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include "canvas2D/Canvas.hpp"

class Example {
public:
    Example();

    void onDraw();
    void onMouse(const glm::vec2& mouse);
    void onResize(const glm::vec2& size);
    void onKey(int k, int a, int m);
private:
    canvas2D::Canvas canvas;
};

#endif //EXAMPLE_HPP
