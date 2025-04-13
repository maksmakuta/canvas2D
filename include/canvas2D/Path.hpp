#ifndef PATH_HPP
#define PATH_HPP
#include <vector>
#include <glm/vec2.hpp>

namespace canvas2D {

    enum class LineCap {
        Butt,
        Round,
        Square
    };

    enum class LineJoin {
        Round,
        Bevel,
        Miter
    };

    class Path {
    public:
        Path() = default;

        void moveTo(float x, float y);
        void lineTo(float x, float y);
        void arcTo(float x1, float y1, float x2, float y2, float r);
        void bezierTo(float x1, float y1, float x2, float y2);
        void bezierTo(float x1, float y1, float x2, float y2, float x3, float y3);

        void moveTo(const glm::vec2& p);
        void lineTo(const glm::vec2& p);
        void arcTo(const glm::vec2& p1, const glm::vec2& p2, float r);
        void bezierTo(const glm::vec2& p1, const glm::vec2& p2);
        void bezierTo(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3);

        void rect(float x,float y,float w, float h);
        void roundRect(float x,float y,float w, float h, const std::initializer_list<float>& r);
        void arc(float x,float y,float r, float start, float end, bool ccw = false);
        void ellipse(float x, float y, float rx, float ry, float rot, float start, float end, bool ccw = false);
    private:
        std::vector<glm::vec2> m_data;
    };
}

#endif //PATH_HPP
