#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

namespace canvas2D {

    class Color {
    public:
        explicit Color(uint32_t _hex = 0xFF000000);
        Color(float r,float g,float b,float a);

        void set(uint32_t _hex);
        void set(float r,float g,float b,float a);

        [[nodiscard]] uint32_t get() const;

        [[nodiscard]] float getR() const;
        [[nodiscard]] float getG() const;
        [[nodiscard]] float getB() const;
        [[nodiscard]] float getA() const;

    private:
        // store color data in format: 0xAARRGGBB
        uint32_t m_value;
    };

}

#endif //COLOR_HPP
