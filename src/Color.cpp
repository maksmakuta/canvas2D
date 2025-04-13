#include "canvas2D/Color.hpp"

namespace canvas2D {
    namespace detail {

        inline uint32_t toByte(const float f) {
            return static_cast<uint32_t>(f * 255.f);
        }

        inline float toFloat(const uint32_t byte) {
            return static_cast<float>(byte & 0xFF) / 255.f;
        }

    }

    Color::Color(const uint32_t _hex) : m_value(_hex){}

    Color::Color(const float r, const float g, const float b, const float a) : m_value(0) {
        m_value |= detail::toByte(a) << 24;
        m_value |= detail::toByte(r) << 16;
        m_value |= detail::toByte(g) << 8;
        m_value |= detail::toByte(b);
    }

    void Color::set(uint32_t _hex) {
        m_value = _hex;
    }

    void Color::set(const float r, const float g, const float b, const float a) {
        m_value = 0;
        m_value |= detail::toByte(a) << 24;
        m_value |= detail::toByte(r) << 16;
        m_value |= detail::toByte(g) << 8;
        m_value |= detail::toByte(b);
    }

    uint32_t Color::get() const {
        return m_value;
    }

    float Color::getA() const {
        return detail::toFloat(m_value >> 24);
    }

    float Color::getR() const {
        return detail::toFloat(m_value >> 16);
    }

    float Color::getG() const{
        return detail::toFloat(m_value >> 8);
    }

    float Color::getB() const {
        return detail::toFloat(m_value);
    }

}
