#include "canvas2D/Path.hpp"

#include <glm/detail/func_trigonometric.inl>
#include <glm/gtc/constants.hpp>

namespace canvas2D{

    Path::Path() = default;

    glm::vec2 transform(const glm::vec2& vec, const glm::mat4& mat) {
        auto v = glm::vec4{vec,0,1};
        v = mat * v;
        return {v.x,v.y};
    }

    void Path::addPath(const Path& p, const glm::mat4 &m) {
        if (p.data().empty()) {
            return;
        }


        if (m != glm::mat4{1.f}) {
            for (const auto& item : p.m_data) {
                m_data.push_back(transform(item,m));
            }
        }else {
            m_data.insert(m_data.end(),p.data().begin(),p.data().end());
        }
    }


    void Path::moveTo(const float x, const float y) {
        if (m_data.empty() || m_data.front() != internal::PATH_END) {
            closePath();
        }
        m_data.emplace_back(x,y);
    }

    void Path::lineTo(const float x, const float y) {
        m_data.emplace_back(x,y);
    }

    void Path::rect(const float x, const float y, const float w, const float h) {
        moveTo(x,y);
        lineTo(x+w,y);
        lineTo(x+w,y+h);
        lineTo(x,y+h);
    }

    void Path::arc(const float x, const float y, const float r, const float startAngle, const float endAngle, const bool ccw) {
        ellipse(x,y,r,r,0,startAngle,endAngle,ccw);
    }

    bool onSameLine(const glm::vec2& a,const glm::vec2& b,const glm::vec2& c) {
        const glm::vec2 ab = b - a;
        const glm::vec2 ac = c - a;
        const float cross = ab.x * ac.y - ab.y * ac.x;
        return std::abs(cross) < 0.0001f;
    }

    void Path::arcTo(const float x1, const float y1, const float x2, const float y2, const float r) {
        if (m_data.empty() || m_data.front() == internal::PATH_END) {
            return;
        }

        if (r < 0.f) {
            return;
        }

        const auto& P0 = m_data.front();
        const auto P1 = glm::vec2{x1,y1};
        const auto P2 = glm::vec2{x2,y2};

        if (P0 == P1 || P1 == P2 || r <= 0.00001f || onSameLine(P0,P1,P2)) {
            m_data.push_back(P1);
        }

        const auto dir1 = P0 - P1;
        if (dir1.x == 0 && dir1.y == 0) {
            return;
        }

        const auto dir2 = P2 - P1;
        if (dir2.x == 0 && dir2.y == 0) {
            return;
        }

        const auto dir1_unit = glm::normalize(dir1);
        const auto dir2_unit = glm::normalize(dir2);

        if (const auto dp = dot(dir1_unit, dir2_unit); std::abs(dp) > 0.999999f) {
            return;
        }
        const auto angle = std::acos(dot(dir1_unit, dir2_unit));
        const auto distToTangent = r / std::tanf(0.5f * angle);

        const auto linePointAt = [](const glm::vec2& p, const float t, const glm::vec2& dir) {
                return p + t * dir;
        };

        const auto findCenter = [&linePointAt](const glm::vec2& T, const glm::vec2& d, const float r, const glm::vec2& dirTan) {
            auto dn = std::abs(d.x) < std::abs(d.y)
                ? glm::vec2(1, -d.x / d.y)
                : glm::vec2(-d.y / d.x, 1);

            if (glm::dot(dn, dirTan) < 0) {
                dn.x = -dn.x;
                dn.y = -dn.y;
            }

            return linePointAt(T, r / glm::length(dn), dn);
        };

        const auto T1 = linePointAt(P1, distToTangent, dir1_unit);
        const auto T2 = linePointAt(P1, distToTangent, dir2_unit);

        const auto dirT2_T1 = T2 - T1;
        const auto dirT1_T2 = -dirT2_T1;
        const auto C1 = findCenter(T1, dir1_unit, r, dirT2_T1);
        const auto C2 = findCenter(T2, dir2_unit, r, dirT1_T2);

        const auto deltaC = C2 - C1;
        if (deltaC.x * deltaC.x + deltaC.y * deltaC.y > 1e-4) {
            // here error
            return;
        }

        const auto C = C1 + 0.5f * deltaC;
        float dot = glm::dot(glm::normalize(C), glm::normalize(T1));
        dot = glm::clamp(dot, -1.0f, 1.0f);
        const auto angle1 = acosf(dot);
        const auto angle2 = angle + angle1;
        arc(C.x,C.y,r,angle1,angle2);
    }

    void Path::quadraticCurveTo(const float cpx, const float cpy, const float x, const float y) {
        if (m_data.empty() || m_data.front() == internal::PATH_END) {
            return;
        }

        const auto& a = m_data.front();
        const auto b = glm::vec2{cpx,cpy};
        const auto c = glm::vec2{x,y};
        auto t = 0.f;
        while (t <= 1.f) {
            const auto t1 = mix(a,b,t);
            const auto t2 = mix(b,c,t);
            m_data.push_back(mix(t1,t2,t));
            t += 0.1f;
        }
    }

    void Path::bezierCurveTo(const float cp1x, const float cp1y, const float cp2x, const float cp2y, const float x, const float y) {
        if (m_data.empty() || m_data.front() == internal::PATH_END) {
            moveTo(0,0);
        }

        const auto& a = m_data.front();
        const auto b = glm::vec2{cp1x,cp1y};
        const auto c = glm::vec2{cp2x,cp2y};
        const auto d = glm::vec2{x,y};
        auto t = 0.f;
        while (t <= 1.f) {
            const auto t1 = mix(a,b,t);
            const auto t2 = mix(b,c,t);
            const auto t3 = mix(c,d,t);

            const auto r1 = mix(t1,t2,t);
            const auto r2 = mix(t2,t3,t);

            m_data.push_back(mix(r1,r2,t));
            t += 0.1f;
        }
    }

    void Path::ellipse(const float x, const float y, const float radiusX, const float radiusY, const float rotation,
                       float startAngle, float endAngle, bool ccw) {

        if (radiusX < 0 || radiusY < 0) {
            return;
        }

        if ((!ccw && (endAngle - startAngle) > glm::two_pi<float>()) ||
            (ccw) && (startAngle - endAngle) > glm::two_pi<float>()) {
            startAngle = 0.f;
            endAngle = glm::two_pi<float>();
            ccw = true;
        }

        const auto center = glm::vec2{x,y};
        const auto r = glm::vec2{radiusX,radiusY};

        float a = ccw ? startAngle : endAngle;
        while (a <= (!ccw ? startAngle : endAngle)) {
            const auto unit = glm::vec2{cosf(a), sinf(a)};
            m_data.push_back(center + unit * r);
            a += glm::radians(5.f);
            if (a > (!ccw ? startAngle : endAngle)) {
                a = (!ccw ? startAngle : endAngle);
            }
        }

    }

    void Path::closePath() {
        if (!m_data.empty() && m_data.front() != internal::PATH_END)
            m_data.emplace_back(internal::PATH_END);
    }

    std::vector<glm::vec2> Path::data() const {
        return m_data;
    }

    void Path::clear() {
        m_data.clear();
    }
}
