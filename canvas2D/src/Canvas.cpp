#include "canvas2D/Canvas.hpp"

#include "glad/gl.h"

#include <glm/gtc/matrix_transform.hpp>

namespace canvas2D{

    namespace OpenGL {

        bool init(const GLADloadfunc l) {
            return gladLoadGL(l);
        }

    }

    Canvas::Canvas() = default;

    void Canvas::scale(const float x, const float y){
        m_transform = glm::scale(m_transform,glm::vec3{x,y,1});
    }

    void Canvas::rotate(const float angle){
        m_transform = glm::rotate(m_transform,angle,glm::vec3{1,0,0});
    }

    void Canvas::translate(const float x, const float y){
        m_transform = glm::translate(m_transform,glm::vec3{x,y,0});
    }

    void Canvas::transform(const float a, const float b, const float c, const float d, const float e, const float f){
        m_transform *= glm::mat4{
            a,b,c,0,
            d,e,f,0,
            0,0,1,0,
            0,0,0,1
        };
    }

    glm::mat4 Canvas::getTransform() const {
        return m_transform;
    }

    void Canvas::setTransform(const float a, const float b, const float c, const float d, const float e, const float f){
        m_transform = glm::mat4{
            a,b,c,0,
            d,e,f,0,
            0,0,1,0,
            0,0,0,1
        };
    }

    void Canvas::setTransform(const glm::mat4& mat){
        m_transform = mat;
    }

    void Canvas::resetTransform(){
        m_transform = glm::mat4{1.f};
    }


    /**
     *
    *
    *void Canvas::clearRect(float x, float y, float w, float h) {
        glEnable(GL_SCISSOR_TEST);
        glScissor(x, y, w, h);
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);
    }
     *
     */

}
