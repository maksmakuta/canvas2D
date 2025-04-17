#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

namespace canvas2D {

    namespace internal {
        constexpr auto PATH_END = glm::vec2{std::numeric_limits<float>::infinity()};
    }

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
        Path();

        void addPath(const Path&, const glm::mat4& m = {1.f});

        void moveTo(float x, float y);
        void lineTo(float x, float y);
        void rect(float x, float y, float w, float h);
        void arc(float x, float y, float r, float startAngle, float endAngle, bool ccw = false);
        void arcTo(float x1, float y1, float x2, float y2, float r);
        void quadraticCurveTo(float cpx, float cpy, float x, float y);
        void bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);
        void ellipse(float x, float y, float radiusX, float radiusY, float rotation,
                     float startAngle, float endAngle, bool ccw = false);
        void closePath();

        [[nodiscard]] std::vector<glm::vec2> data() const;
        void clear();

    private:
        std::vector<glm::vec2> m_data;
    };

}

#endif //PATH_HPP
