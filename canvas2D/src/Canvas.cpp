#include "canvas2D/Canvas.hpp"

#include "glad/gl.h"

namespace canvas2D{

    namespace OpenGL {

        bool init(const GLADloadfunc l) {
            return gladLoadGL(l);
        }

    }

    Canvas::Canvas() {

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
