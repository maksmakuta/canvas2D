#include "Example.hpp"

Example::Example() = default;

void Example::onDraw(){
    canvas.clear(canvas2D::Color::Red);

    canvas.beginPath();
    canvas.rect(0,0,25,25);
    canvas.fill();
}

void Example::onMouse(const glm::vec2& mouse){

}

void Example::onResize(const glm::ivec2& size){
    canvas.resize(size.x,size.y);
}

void Example::onKey(int k, int a, int m){

}
