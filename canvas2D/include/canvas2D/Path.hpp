#ifndef PATH_HPP
#define PATH_HPP

#include <variant>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

namespace canvas2D {

    namespace internal {
        struct MoveTo {
            glm::vec2 point;
        };

        struct LineTo {
            glm::vec2 point;
        };

        struct Rect {
            glm::vec2 origin; glm::vec2 size;
        };

        struct Arc {
            glm::vec2 center;
            float radius;
            float startAngle;
            float endAngle;
            bool counterclockwise;
        };

        struct ArcTo {
            glm::vec2 p1, p2;
            float radius;
        };

        struct QuadraticCurveTo {
            glm::vec2 control;
            glm::vec2 end;
        };

        struct BezierCurveTo {
            glm::vec2 control1;
            glm::vec2 control2;
            glm::vec2 end;
        };

        struct Ellipse {
            glm::vec2 center;
            float radiusX, radiusY;
            float rotation;
            float startAngle, endAngle;
            bool counterclockwise;
        };

        struct ClosePath {};

        using PathCommand = std::variant<
            MoveTo, LineTo, Rect, Arc, ArcTo,
            QuadraticCurveTo, BezierCurveTo,
            Ellipse, ClosePath
        >;
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

        [[nodiscard]] const std::vector<internal::PathCommand>& commands() const;
        void clear();

    private:
        std::vector<internal::PathCommand> m_commands;
    };

}

#endif //PATH_HPP
