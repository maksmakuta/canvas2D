#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include "canvas2D/Canvas.hpp"

class Example {
public:
    Example();

    void onDraw(canvas2D::Canvas& canvas);
    void onMouse(const glm::vec2& mouse);
    void onResize(const glm::vec2& size);
    void onKey(int k, int a, int m);
};

#endif //EXAMPLE_HPP
