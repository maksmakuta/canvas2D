#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <glm/vec4.hpp>

namespace canvas2D {

    class Color {
    public:
        float r, g, b, a;

        Color();
        explicit Color(float gray, float alpha = 1.0f);
        Color(float red, float green, float blue, float alpha = 1.0f);
        
        static Color fromRGBA8(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);

        [[nodiscard]] glm::vec4 toVec4() const;

        static Color Red;
        static Color Green;
        static Color Blue;
        static Color White;
        static Color Black;
        static Color Transparent;
        static Color Gray;
    };

}

#endif //COLOR_HPP
