#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glm/vec2.hpp>

namespace canvas2D {

    class Texture {
    public:
        explicit Texture(const std::string& file);
        Texture(int w ,int h, const void* data = nullptr);

    private:
        glm::uvec2 m_size;
    };
}

#endif //TEXTURE_HPP
