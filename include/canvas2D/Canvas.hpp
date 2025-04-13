#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <string>

#include "Color.hpp"
#include "Path.hpp"
#include "Texture.hpp"

namespace canvas2D {

    enum class FillRule {
        NonZero,
        EvenOdd
    };

    class Box{};

    class Canvas {
    public:
        Canvas() = default;
        ~Canvas() = default;

        void clear();
        void setClearColor(const Color&);

        //state operations
        void save();
        void restore();
        void reset();

        // matrix operations
        void scale(float x,float y);
        void rotate(float a);
        void transform(float x,float y);
        void transform(float a,float b,float c,float d,float e,float f);

        void setTransform(float a,float b,float c,float d,float e,float f);
        //void setTransform(const glm::mat3x2&);

        // rect methods
        void clearRect(float x, float y, float w, float h);
        void fillRect(float x, float y, float w, float h);
        void strokeRect(float x, float y, float w, float h);

        void beginPath();
        void fill(FillRule = FillRule::NonZero);
        void fill(const Path&, FillRule = FillRule::NonZero);
        void stroke(FillRule = FillRule::NonZero);
        void stroke(const Path&, FillRule = FillRule::NonZero);
        void clip(FillRule = FillRule::NonZero);
        void clip(const Path&, FillRule = FillRule::NonZero);

        // text rendering
        void fillText(const std::string& text, float x,float y);
        void strokeText(const std::string& text, float x,float y);
        Box measureText(const std::string& text, float x,float y);

        void drawImage(const Texture& image, float x, float y);
        void drawImage(const Texture& image, float x, float y, float w, float h);
        void drawImage(const Texture& image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);

    };

}

#endif //CANVAS_HPP
