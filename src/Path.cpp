#include "canvas2D/Path.hpp"

#include <glm/detail/func_geometric.inl>
#include <glm/detail/func_trigonometric.inl>
#include <glm/gtc/constants.hpp>

namespace canvas2D {
    constexpr auto PATH_FLAG = glm::vec2(std::numeric_limits<float>::min());

    void Path::moveTo(float x, float y) {
        if (!m_data.empty()) {
            m_data.push_back(PATH_FLAG);
        }
        m_data.emplace_back(x,y);
    }

    void Path::lineTo(float x, float y) {
        m_data.emplace_back(x,y);
    }

    float cross(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c) {
        const float dxc = a.x - b.x;
        const float dyc = a.y - b.y;
        const float dxl = c.x - b.x;
        const float dyl = c.y - b.y;
        return dxc * dyl - dyc * dxl;
    }

    float dot(const glm::vec2& a, const glm::vec2& b) {
        return a.x * b.x + a.y * b.y;
    }

    glm::vec2 findCenter(const glm::vec2& T,const glm::vec2& d, const float r, const glm::vec2& dirTan) {
        const auto dn =
          std::abs(d.x) < std::abs(d.y)
            ? glm::vec2(1, -d.x / d.y)
            : glm::vec2(-d.y / d.x, 1);

        if (dot(dn, dirTan) < 0) {
            dn.x = -dn.x;
            dn.y = -dn.y;
        }

        return T + r / glm::length(dn) * dn;
    }

    float getAngle(const glm::vec2& a,const glm::vec2& b) {
        const auto t = b - a;
        return std::atan2(t.y, t.x);
    }

    void Path::arcTo(const float x1, const float y1, const float x2, const float y2, const float r) {
        if (r < 0)
            return;

        const auto a = m_data.front();
        const auto b = glm::vec2{x1,y1};
        const auto c = glm::vec2{x2,y2};
        if (r == 0.0f || a == b || b == c || cross(a,b,c) < 0.0001f) {
            lineTo(b);
            return;
        }

        const auto dir1_unit = glm::normalize(a - b);
        const auto dir2_unit = glm::normalize(c - b);
        if (std::abs(dot(dir1_unit, dir2_unit)) > 0.999999) {
          return;
        }
        const auto angle = std::acos(dot(dir1_unit, dir2_unit));
        const auto distToTangent = r / std::tanf(0.5f * angle);

        const auto T1 = b + distToTangent * dir1_unit;
        const auto T2 = b + distToTangent * dir2_unit;

        const auto dirT2_T1 = glm::vec2(T2.x - T1.x, T2.y - T1.y);
        const auto dirT1_T2 = glm::vec2(-dirT2_T1.x, -dirT2_T1.y);
        const auto C1 = findCenter(T1, dir1_unit, r, dirT2_T1);
        const auto C2 = findCenter(T2, dir2_unit, r, dirT1_T2);

        const auto deltaC = glm::vec2(C2.x - C1.x, C2.y - C1.y);
        if (deltaC.x * deltaC.x + deltaC.y * deltaC.y > 1e-4f) {
            //Error here
            return;
        }
        const auto C = glm::vec2(C1.x + 0.5 * deltaC.x, C1.y + 0.5 * deltaC.y);

        const auto a1 = getAngle(C,T1);
        const auto a2 = getAngle(C,T2);
        arc(C.x,C.y,r,a1,a2);
    }

    void Path::bezierTo(const float x1, const float y1, const float x2, const float y2) {
        if (m_data.front() == PATH_FLAG) {
            m_data.emplace_back(0,0);
        }

        constexpr float dt = 0.1f;
        constexpr auto a = m_data.front();
        constexpr auto b = glm::vec2{x1,y1};
        constexpr auto c = glm::vec2{x2,y2};
        float t = 0.f;
        while (t <= 1.f) {
            auto t1 = glm::mix(a,b,t);
            auto t2 = glm::mix(b,c,t);
            lineTo(mix(t1,t2,t));
            t += dt;
        }
    }

    void Path::bezierTo(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3) {
        if (m_data.front() == PATH_FLAG) {
            m_data.emplace_back(0,0);
        }

        constexpr float dt = 0.1f;
        constexpr auto a = m_data.front();
        constexpr auto b = glm::vec2{x1,y1};
        constexpr auto c = glm::vec2{x2,y2};
        constexpr auto d = glm::vec2{x3,y3};
        float t = 0.f;
        while (t <= 1.f) {
            auto t1 = glm::mix(a,b,t);
            auto t2 = glm::mix(b,c,t);
            auto t3 = glm::mix(c,d,t);

            auto r1 = glm::mix(t1,t2,t);
            auto r2 = glm::mix(t2,t3,t);

            lineTo(mix(r1,r2,t));
            t += dt;
        }
    }

    void Path::moveTo(const glm::vec2& p){
        moveTo(p.x,p.y);
    }

    void Path::lineTo(const glm::vec2& p){
        lineTo(p.x,p.y);
    }

    void Path::arcTo(const glm::vec2& p1, const glm::vec2& p2, const float r){
        arcTo(p1.x,p1.y,p2.x,p2.y,r);
    }

    void Path::bezierTo(const glm::vec2& p1, const glm::vec2& p2){
        bezierTo(p1.x,p1.y,p2.x,p2.y);
    }

    void Path::bezierTo(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3){
        bezierTo(p1.x,p1.y,p2.x,p2.y,p3.x,p3.y);
    }

    void Path::rect(const float x, const float y, const float w, const float h) {
        moveTo(x, y);
        lineTo(x+w, y);
        lineTo(x+w, y+h);
        lineTo(x, y+h);
        moveTo(x, y);
    }

    void Path::roundRect(float x,float y,float w, float h, const std::initializer_list<float>& r) {
        if (r.size() == 0 || r.size() > 4) {
            return;
        }
        std::vector<glm::vec2> rList;
        for (const auto& item : r) {
            rList.emplace_back(item);
        }

        glm::vec2 upperLeft;
        glm::vec2 upperRight;
        glm::vec2 lowerLeft;
        glm::vec2 lowerRight;

        if (r.size() == 1) {
            upperLeft = upperRight = lowerLeft = lowerRight = rList[0];
        }else if (r.size() == 2) {
            upperLeft = lowerRight = rList[0];
            upperRight = lowerLeft = rList[1];
        }else if (r.size() == 3) {
            upperLeft = rList[0];
            upperRight = lowerLeft = rList[1];
            lowerRight = rList[2];
        }else {
            upperLeft = rList[0];
            upperRight = rList[1];
            lowerRight = rList[2];
            lowerLeft = rList[3];
        }

        float top = upperLeft.x + upperRight.x;
        float right =  upperRight.y + lowerRight.y;
        float bottom = lowerRight.x + lowerLeft.x;
        float left = upperLeft.y + lowerLeft.y;
        float scale = std::min(std::min(w / top, h / right), std::min(w / bottom, h / left));
        if (scale < 1.f) {
            upperLeft *= scale;
            upperRight *= scale;
            lowerLeft *= scale;
            lowerRight *= scale;
        }

        moveTo(x + upperLeft.x, y);
        lineTo(x + w - upperRight.x, y);
        arcTo(x + w,y,x + w, y + upperRight.y,length(upperRight));
        lineTo(x + w, y + h - lowerRight.y);
        arcTo(x + w, y + h - lowerRight.y,x + w - lowerRight.y, y + h,glm::length(lowerRight));
        lineTo(x + lowerLeft.x, y + h);
        arcTo(x + lowerLeft.x, y + h,x, y + h - lowerLeft.y,glm::length(lowerLeft));
        lineTo(x, y + upperLeft.y);
        arcTo(x, y + upperLeft.y,x + upperLeft.x, y,glm::length(upperLeft));
        moveTo(x,y);
    }

    void Path::arc(const float x, const float y, const float r, const float start, const float end, const bool ccw) {
        ellipse(x,y,r,r,0,start,end,ccw);
    }

    void Path::ellipse(const float x, const float y, const float rx, const float ry, const float rot,
                       float start, float end, const bool ccw){

        if (rx < 0 || ry < 0)
            return;

        if ((!ccw and end - start >= glm::two_pi<float>()) or (ccw && (start - end) >= glm::two_pi<float>())){
            start = 0.f;
            end = glm::two_pi<float>();
        }

        constexpr auto center = glm::vec2{x,y};
        constexpr auto dir = glm::vec2{rx,ry};
        constexpr auto dt = glm::radians(5.f);
        float t = start;
        while (t <= end) {
            if (t > end) {
                t = end;
            }
            auto unit = glm::vec2{cosf(t),sinf(t)};
            lineTo(center + unit * dir);
            t += dt;
        }
    }

}
