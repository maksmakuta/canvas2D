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

        uint handle() const;
        void use() const;

        void setInt(const std::string& name, int value) const;
        void setUInt(const std::string& name, uint value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setMat3(const std::string& name, const glm::mat3& value) const;
        void setMat4(const std::string& name, const glm::mat4& value) const;
    private:
        uint m_handle{0};
    };
}

#endif //SHADER_HPP
