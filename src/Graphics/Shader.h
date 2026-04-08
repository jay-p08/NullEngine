#pragma once
#include <string>
#include <glm/glm.hpp>

namespace NullEngine
{

    class Shader
    {
    public:
        Shader(const std::string &vertexSrc, const std::string &fragmentSrc);
        ~Shader();

        void Bind() const;   // 이 쉐이더를 사용하겠다
        void Unbind() const; // 사용 중지

        // 유니폼 변수 설정 (나중에 색상이나 행렬을 보낼 때 사용)
        void SetInt(const std::string &name, int value);
        void SetFloat3(const std::string &name, const glm::vec3 &value);

    private:
        uint32_t m_RendererID; // OpenGL이 부여한 쉐이더 프로그램 ID
    };

}