#include "Example.hpp"

Example::Example() = default;

void Example::onDraw(){
    canvas.clear(canvas2D::Color::Red);
    canvas.clearRect(200,200,500,500);
}

void Example::onMouse(const glm::vec2& mouse){

}

void Example::onResize(const glm::vec2& size){

}

void Example::onKey(int k, int a, int m){

}
