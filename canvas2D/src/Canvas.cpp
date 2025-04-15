#include "canvas2D/Canvas.hpp"

#include "glad/gl.h"

namespace canvas2D{

    namespace OpenGL {

        bool init(const GLADloadfunc l) {
            return gladLoadGL(l);
        }

    }

    Canvas::Canvas() {
        glEnable(GL_BLEND);
    }

}
