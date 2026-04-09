#include "Graphics/Shader.h"
#include "Core/Log.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>

namespace NullEngine
{
    Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
    {
        std::string vCode = ReadFile(vertexPath);
        std::string fCode = ReadFile(fragmentPath);
        const char *vShaderCode = vCode.c_str();
        const char *fShaderCode = fCode.c_str();

        uint32_t vertex, fragment;

        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");

        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");

        // Shader Program
        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertex);
        glAttachShader(m_RendererID, fragment);
        glLinkProgram(m_RendererID);
        CheckCompileErrors(m_RendererID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader::~Shader() { glDeleteProgram(m_RendererID); }
    void Shader::Bind() const { glUseProgram(m_RendererID); }
    void Shader::Unbind() const { glUseProgram(0); }

    std::string Shader::ReadFile(const std::string &filepath)
    {
        std::ifstream file(filepath);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    void Shader::CheckCompileErrors(uint32_t shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                NE_CORE_ERROR("Shader Compilation Error ({0}):\n{1}", type, infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                NE_CORE_ERROR("Shader Linking Error ({0}):\n{1}", type, infoLog);
            }
        }
    }

    void Shader::SetMat4(const std::string &name, const glm::mat4 &value)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void Shader::SetInt(const std::string &name, int value)
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }
}