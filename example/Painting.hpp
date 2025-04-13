#ifndef PAINTING_HPP
#define PAINTING_HPP

#include "canvas2D/Canvas.hpp"

class Painter {
public:
    Painter() = default;

    void onDraw(canvas2D::Canvas& canvas);

    void onResize(const glm::vec2& size);
    void onMouse(const glm::vec2& pos);
    void onKey(int k, int a, int m);
};


#endif //PAINTING_HPP
