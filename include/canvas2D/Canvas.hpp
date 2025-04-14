#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <string>

#include "Color.hpp"
#include "Path.hpp"
#include "Texture.hpp"

#include <glm/mat4x4.hpp>

#include "Shader.hpp"

namespace canvas2D {

    typedef void (*api_proc)();
    typedef api_proc (*loader)(const char *name);

    void loadOpenGL(loader func);

    enum class FillRule {
        NonZero,
        EvenOdd
    };

    class Box{};

    class Canvas {
    public:
        Canvas() = default;
        ~Canvas() = default;

        void onResize(const glm::vec2& size);

        void clear();
        void setClearColor(const Color&);

        //state operations
        void save();
        void restore();
        void reset();

        // matrix operations
        void scale(float x,float y);
        void rotate(float a);
        void translate(float x,float y);
        void transform(float a,float b,float c,float d,float e,float f);

        [[nodiscard]] glm::mat4 getTransform() const;
        void setTransform(float a,float b,float c,float d,float e,float f);
        void setTransform(const glm::mat4&);
        void resetTransform();

        // rect methods
        void clearRect(float x, float y, float w, float h);
        void fillRect(float x, float y, float w, float h);
        void strokeRect(float x, float y, float w, float h);

        // drawing methods
        void fill(const Path&, FillRule = FillRule::NonZero);
        void stroke(const Path&, FillRule = FillRule::NonZero);
        void clip(const Path&, FillRule = FillRule::NonZero);

        // text rendering
        void fillText(const std::string& text, float x,float y);
        void strokeText(const std::string& text, float x,float y);
        Box measureText(const std::string& text, float x,float y);

        // image rendering
        void drawImage(const Texture& image, float x, float y);
        void drawImage(const Texture& image, float x, float y, float w, float h);
        void drawImage(const Texture& image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);

    private:
        glm::mat4 m_mat{1.f}, m_proj{1.f};
        Shader m_shader;
        uint m_vao{0}, m_vbo{0};
    };

}

#endif //CANVAS_HPP
