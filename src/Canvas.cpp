#include "canvas2D/Canvas.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "gl/gl.h"

namespace canvas2D {

    void loadOpenGL(const loader func) {
        gladLoadGL(func);
    }

    void Canvas::onResize(const glm::vec2 &size) {
        glViewport(0,0,static_cast<int>(size.x),static_cast<int>(size.y));
        m_proj = glm::ortho(0.f,size.x,size.y,0.f);
    }

    void Canvas::clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Canvas::setClearColor(const Color& c) {
        glClearColor(c.getR(),c.getG(),c.getB(),c.getA());
    }

    void Canvas::save(){
        //TODO(not implemented)
    }

    void Canvas::restore(){
        //TODO(not implemented)
    }

    void Canvas::reset(){
        //TODO(not implemented)
    }

    void Canvas::scale(const float x, const float y){
        m_mat = glm::scale(m_mat,glm::vec3{x,y,1});
    }

    void Canvas::rotate(const float a){
        m_mat = glm::rotate(m_mat,a,glm::vec3{1,0,0});
    }

    void Canvas::translate(const float x, const float y){
        m_mat = glm::translate(m_mat,glm::vec3{x,y,1});
    }

    void Canvas::transform(const float a, const float b, const float c, const float d, const float e, const float f){
        const auto mat = glm::mat4{
            a,b,c,0,
            d,e,f,0,
            0,0,1,0,
            0,0,0,1
        };

        m_mat *= mat;
    }

    glm::mat4 Canvas::getTransform() const {
        return m_mat;
    }

    void Canvas::setTransform(float a,float b,float c,float d,float e,float f) {
        m_mat = glm::mat4{
            a,b,c,0,
            d,e,f,0,
            0,0,1,0,
            0,0,0,1
        };
    }

    void Canvas::setTransform(const glm::mat4& mat) {
        m_mat = mat;
    }

    void Canvas::resetTransform() {
        m_mat = glm::identity<float>();
    }

    void Canvas::clearRect(const float x, const float y, const float w, const float h){
        glScissor(static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h));
        glEnable(GL_SCISSOR_TEST);
    }

    void Canvas::fillRect(const float x, const float y, const float w, const float h){
        Path temp;
        temp.rect(x,y,w,h);
        fill(temp);
    }

    void Canvas::strokeRect(const float x, const float y, const float w, const float h){
        Path temp;
        temp.rect(x,y,w,h);
        stroke(temp);
    }

    void Canvas::fill(FillRule){
        //TODO(not implemented)
    }

    void Canvas::fill(const Path&, FillRule){
        //TODO(not implemented)
    }

    void Canvas::stroke(FillRule){
        //TODO(not implemented)
    }

    void Canvas::stroke(const Path&, FillRule){
        //TODO(not implemented)
    }

    void Canvas::clip(FillRule){
        //TODO(not implemented)
    }

    void Canvas::clip(const Path&, FillRule){
        //TODO(not implemented)
    }

    void Canvas::fillText(const std::string& text, float x,float y){
        //TODO(not implemented)
    }

    void Canvas::strokeText(const std::string& text, float x,float y){
        //TODO(not implemented)
    }

    Box Canvas::measureText(const std::string& text, float x,float y){
        //TODO(not implemented)
        return {};
    }

    void Canvas::drawImage(const Texture& image, float x, float y){
        //TODO(not implemented)
    }

    void Canvas::drawImage(const Texture& image, float x, float y, float w, float h){
        //TODO(not implemented)
    }

    void Canvas::drawImage(const Texture& image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh){
        //TODO(not implemented)
    }

}
