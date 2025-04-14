#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glm/glm.hpp>

namespace canvas2D {

    class Shader {
    public:
        Shader() = default;

        void fromMem(const std::string& vert,const std::string& frag);
        void fromFile(const std::string& vert,const std::string& frag);

        uint handle();
        void use() const;

        void setInt(const std::string& name, int value);
        void setUInt(const std::string& name, uint value);
        void setFloat(const std::string& name, float value);
        void setVec2(const std::string& name, const glm::vec2& value);
        void setVec3(const std::string& name, const glm::vec3& value);
        void setVec4(const std::string& name, const glm::vec4& value);
        void setMat3(const std::string& name, const glm::mat3& value);
        void setMat4(const std::string& name, const glm::mat4& value);
    private:
        uint m_handle{0};
    };
}

#endif //SHADER_HPP
