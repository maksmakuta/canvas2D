#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <string>
#include <glm/fwd.hpp>

#include "Color.hpp"
#include "Image.hpp"
#include "Path.hpp"
#include "glad/gl.h"

namespace canvas2D{

    namespace OpenGL {
        bool init(GLADloadfunc);
    }

    enum class FillRule {
        NonZero,
        EvenOdd
    };

    struct Gradient{};
    struct Pattern{};
    struct TextMetrics{};

    class Canvas{
    public:
        Canvas();

        // control canvas
        void clear(const Color & color);
        void resize(int w, int h);

        // matrix operations
        void scale(float x, float y);
        void rotate(float angle);
        void translate(float x, float y);
        void transform(float a, float b, float c, float d, float e, float f);
        [[nodiscard]] glm::mat4 getTransform() const;
        void setTransform(float a, float b, float c, float d, float e, float f);
        void setTransform(const glm::mat4&);
        void resetTransform();

        //gradients/patterns
        Gradient createLinearGradient(double x0, double y0, double x1, double y1);
        Gradient createRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1);
        Gradient createConicGradient(double startAngle, double x, double y);
        Pattern  createPattern(const Image& image, const std::string& repetition);

        // rect functions
        void clearRect(float x, float y, float w, float h);
        void fillRect(float x, float y, float w, float h);
        void strokeRect(float x, float y, float w, float h);

        //draw api
        void beginPath();
        void fill(FillRule fillRule = FillRule::NonZero);
        void fill(const Path& path, FillRule fillRule = FillRule::NonZero);
        void stroke();
        void stroke(const Path& path);
        void clip(FillRule fillRule = FillRule::NonZero);
        void clip(const Path& path, FillRule fillRule = FillRule::NonZero);
        bool isPointInPath(float x, float y, FillRule fillRule = FillRule::NonZero);
        bool isPointInPath(const Path& path, float x, float y, FillRule fillRule = FillRule::NonZero);
        bool isPointInStroke(float x, float y);
        bool isPointInStroke(const Path& path, float x, float y);

        //text drawing
        void fillText(const std::string& text, float x, float y, float maxWidth = -1);
        void strokeText(const std::string& text, float x, float y, float maxWidth = -1);
        TextMetrics measureText(const std::string& text);

        //images
        void drawImage(const Image& image, float dx, float dy);
        void drawImage(const Image& image, float dx, float dy, float dw, float dh);
        void drawImage(const Image& image, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);

        //subset of path api + new functions
        void closePath();
        void moveTo(float x, float y);
        void lineTo(float x, float y);
        void quadraticCurveTo(float cpx, float cpy, float x, float y);
        void bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);
        void arcTo(float x1, float y1, float x2, float y2, float radius);
        void rect(float x, float y, float w, float h);
        void roundRect(float x, float y, float w, float h, const std::initializer_list<float>& radii = {});
        void roundRect(float x, float y, float w, float h, const std::initializer_list<glm::vec2>& radii = {});
        void arc(float x, float y, float radius, float startAngle, float endAngle, bool counterclockwise = false);
        void ellipse(float x, float y, float radiusX, float radiusY, float rotation, float startAngle, float endAngle, bool counterclockwise = false);

    private:
        glm::mat4 m_transform{1.f};
        glm::mat4 m_projection{1.f};
        Path m_path;
    };

};

#endif //CANVAS_HPP
