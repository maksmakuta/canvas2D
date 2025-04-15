#include "canvas2D/Color.hpp"

namespace canvas2D{

    Color::Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
    Color::Color(const float gray, const float alpha) : r(gray), g(gray), b(gray), a(alpha) {}
    Color::Color(const float red, const float green, const float blue, const float alpha)
        : r(red), g(green), b(blue), a(alpha) {}

    Color Color::fromRGBA8(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) {
        return {
            static_cast<float>(red) / 255.0f,
            static_cast<float>(green) / 255.0f,
            static_cast<float>(blue) / 255.0f,
            static_cast<float>(alpha) / 255.0f
        };
    }

    glm::vec4 Color::toVec4() const {
        return {r, g, b, a};
    }

    Color Color::Red        = Color(1.0f, 0.0f, 0.0f);
    Color Color::Green      = Color(0.0f, 1.0f, 0.0f);
    Color Color::Blue       = Color(0.0f, 0.0f, 1.0f);
    Color Color::White      = Color(1.0f, 1.0f, 1.0f);
    Color Color::Black      = Color(0.0f, 0.0f, 0.0f);
    Color Color::Transparent= Color(0.0f, 0.0f, 0.0f, 0.0f);
    Color Color::Gray       = Color(0.5f, 0.5f, 0.5f);

}
