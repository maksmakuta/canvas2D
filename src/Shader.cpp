#include <canvas2D/Shader.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

#include "gl/gl.h"

namespace canvas2D {

    namespace detail {

        std::string toBuffer(const std::string& path) {
            if (std::ifstream file(path); file.is_open()) {
                return (std::stringstream() << file.rdbuf()).str();
            }
            return "";
        }

        uint createShader(const std::string& code, const int type) {
            const char* source = code.c_str();
            const uint shader = glCreateShader(type);
            glShaderSource(shader, 1, &source, nullptr);
            glCompileShader(shader);
            int  success;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success){
                char infoLog[512];
                glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            return shader;
        }

    }

    void Shader::fromMem(const std::string& vert,const std::string& frag) {
        const uint v = detail::createShader(vert,GL_VERTEX_SHADER);
        const uint f = detail::createShader(frag,GL_FRAGMENT_SHADER);
        m_handle = glCreateProgram();
        glAttachShader(m_handle,v);
        glAttachShader(m_handle,f);
        glLinkProgram(m_handle);
        int  success;
        glGetProgramiv(m_handle, GL_LINK_STATUS, &success);
        if(!success){
            char infoLog[512];
            glGetProgramInfoLog(m_handle, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(v);
        glDeleteShader(f);
    }

    void Shader::fromFile(const std::string& vert,const std::string& frag) {
        fromMem(detail::toBuffer(vert),detail::toBuffer(frag));
    }

    uint Shader::handle() const {
        return m_handle;
    }

    void Shader::use() const {
        glUseProgram(m_handle);
    }

    void Shader::setInt(const std::string& name, const int value) const {
        glUniform1i(glGetUniformLocation(m_handle,name.c_str()),value);
    }

    void Shader::setUInt(const std::string& name, const uint value) const {
        glUniform1ui(glGetUniformLocation(m_handle,name.c_str()),value);
    }

    void Shader::setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(m_handle,name.c_str()),value);
    }

    void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
        glUniform2fv(glGetUniformLocation(m_handle,name.c_str()),1,&value[0]);
    }

    void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(m_handle,name.c_str()),1,&value[0]);
    }

    void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(m_handle,name.c_str()),1,&value[0]);
    }

    void Shader::setMat3(const std::string& name, const glm::mat3& value) const {
        glUniformMatrix3fv(glGetUniformLocation(m_handle,name.c_str()),1,GL_FALSE,&value[0][0]);
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
        glUniformMatrix4fv(glGetUniformLocation(m_handle,name.c_str()),1,GL_FALSE,&value[0][0]);
    }

}
