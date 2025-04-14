#include <canvas2D/Shader.hpp>

#include <fstream>
#include <sstream>

namespace canvas2D {

    namespace detail {

        std::string toBuffer(const std::string& path) {
            if (std::ifstream file(path); file.is_open()) {
                return (std::stringstream() << file.rdbuf()).str();
            }
            return "";
        }

    }

    void Shader::fromMem(const std::string& vert,const std::string& frag) {

    }

    void Shader::fromFile(const std::string& vert,const std::string& frag) {
        fromMem(detail::toBuffer(vert),detail::toBuffer(frag));
    }

    uint Shader::handle() {
        return m_handle;
    }

    void Shader::use() const {
        glUseProgram(m_handle);
    }

    void Shader::setInt(const std::string& name, int value);
    void Shader::setUInt(const std::string& name, uint value);
    void Shader::setFloat(const std::string& name, float value);
    void Shader::setVec2(const std::string& name, const glm::vec2& value);
    void Shader::setVec3(const std::string& name, const glm::vec3& value);
    void Shader::setVec4(const std::string& name, const glm::vec4& value);
    void Shader::setMat3(const std::string& name, const glm::mat3& value);
    void Shader::setMat4(const std::string& name, const glm::mat4& value);

}