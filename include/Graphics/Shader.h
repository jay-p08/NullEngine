#pragma once

#include <string>
#include <glm/glm.hpp>

namespace NullEngine
{
    class Shader
    {
    public:
        Shader(const std::string &vertexPath, const std::string &fragmentPath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // Uniform 전송 (색상, 행렬 등)
        void SetInt(const std::string &name, int value);
        void SetFloat3(const std::string &name, const glm::vec3 &value);
        void SetMat4(const std::string &name, const glm::mat4 &value);

    private:
        uint32_t m_RendererID; // OpenGL Shader Program ID
        std::string ReadFile(const std::string &filepath);
        void CheckCompileErrors(uint32_t shader, std::string type);
    };
}