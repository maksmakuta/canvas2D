#include "canvas2D/Path.hpp"

namespace canvas2D{

    Path::Path() = default;

    glm::vec2 transform(const glm::vec2& vec, const glm::mat4& mat) {
        auto v = glm::vec4{vec,0,1};
        v = mat * v;
        return {v.x,v.y};
    }

    void Path::addPath(const Path& p, const glm::mat4 &m) {
        if (p.commands().empty()) {
            return;
        }

        if (!std::holds_alternative<internal::ClosePath>(m_commands.front())) {
            closePath();
        }

        if (m != glm::mat4{1.f}) {
            for (const auto& item : p.m_commands) {
                std::visit(internal::overload{
                    [&m, this](const internal::MoveTo& mt) {
                        m_commands.emplace_back(internal::MoveTo{transform(mt.point,m)});
                    },
                    [&m, this](const internal::LineTo& l) {
                        m_commands.emplace_back(internal::LineTo{transform(l.point,m)});
                    },
                    [&m, this](const internal::ArcTo& a) {
                        m_commands.emplace_back(internal::ArcTo{transform(a.p1,m),transform(a.p2,m),a.radius});
                    },
                    [&m, this](const internal::QuadraticCurveTo& q) {
                        m_commands.emplace_back(internal::QuadraticCurveTo{transform(q.control,m),transform(q.end,m)});
                    },
                    [&m, this](const internal::BezierCurveTo& b) {
                        m_commands.emplace_back(internal::BezierCurveTo{transform(b.control1,m),transform(b.control2,m),transform(b.end,m)});
                    },
                    [&m, this](const internal::Arc& a) {
                        m_commands.emplace_back(internal::Arc{transform(a.center,m),a.radius,a.startAngle,a.endAngle,a.counterclockwise});
                    },
                    [&m, this](const internal::Rect& r) {
                        m_commands.emplace_back(internal::Rect{transform(r.origin,m),r.size});
                    },
                    [&m, this](const internal::Ellipse& e) {
                        m_commands.emplace_back(internal::Ellipse{transform(e.center,m),e.radiusX,e.radiusY,e.rotation,e.startAngle,e.endAngle,e.counterclockwise});
                    },
                    [this](const internal::ClosePath&) {
                        m_commands.emplace_back(internal::ClosePath{});
                    }
                }, item);
            }

        }else {
            m_commands.insert(m_commands.end(),p.commands().begin(),p.commands().end());
        }
    }


    void Path::moveTo(const float x, const float y) {
        m_commands.emplace_back(internal::MoveTo{glm::vec2(x, y)});
    }

    void Path::lineTo(const float x, const float y) {
        m_commands.emplace_back(internal::LineTo{glm::vec2(x, y)});
    }

    void Path::rect(const float x, const float y, const float w, const float h) {
        m_commands.emplace_back(internal::Rect{glm::vec2(x, y), glm::vec2(w, h)});
    }

    void Path::arc(const float x, const float y, const float r, const float startAngle, const float endAngle, const bool ccw) {
        m_commands.emplace_back(internal::Arc{glm::vec2(x, y), r, startAngle, endAngle, ccw});
    }

    void Path::arcTo(const float x1, const float y1, const float x2, const float y2, const float r) {
        m_commands.emplace_back(internal::ArcTo{glm::vec2(x1, y1), glm::vec2(x2, y2), r});
    }

    void Path::quadraticCurveTo(const float cpx, const float cpy, const float x, const float y) {
        m_commands.emplace_back(internal::QuadraticCurveTo{glm::vec2(cpx, cpy), glm::vec2(x, y)});
    }

    void Path::bezierCurveTo(const float cp1x, const float cp1y, const float cp2x, const float cp2y, const float x, const float y) {
        m_commands.emplace_back(internal::BezierCurveTo{
            glm::vec2(cp1x, cp1y),
            glm::vec2(cp2x, cp2y),
            glm::vec2(x, y)
        });
    }

    void Path::ellipse(const float x, const float y, const float radiusX, const float radiusY, const float rotation,
                       const float startAngle, const float endAngle, const bool ccw) {
        m_commands.emplace_back(internal::Ellipse{
            glm::vec2(x, y),
            radiusX,
            radiusY,
            rotation,
            startAngle,
            endAngle,
            ccw
        });
    }

    void Path::closePath() {
        m_commands.emplace_back(internal::ClosePath{});
    }

    const std::vector<internal::PathCommand>& Path::commands() const {
        return m_commands;
    }

    void Path::clear() {
        m_commands.clear();
    }

}
