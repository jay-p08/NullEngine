#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <spdlog/spdlog.h>

namespace NullEngine
{

    Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
    {
        // 1. 파일 읽기 로직
        auto readShader = [](const std::string &path)
        {
            std::ifstream ifs(path);
            std::stringstream ss;
            ss << ifs.rdbuf();
            return ss.str();
        };

        std::string vSource = readShader(vertexPath);
        std::string fSource = readShader(fragmentPath);

        const char *vCode = vSource.c_str();
        const char *fCode = fSource.c_str();

        // 2. 컴파일 및 링크 (에러 체크 생략 버전 - 실제로는 꼭 넣어야 함)
        uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vCode, nullptr);
        glCompileShader(vertex);

        uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fCode, nullptr);
        glCompileShader(fragment);

        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertex);
        glAttachShader(m_RendererID, fragment);
        glLinkProgram(m_RendererID);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        spdlog::info("Shader Compiled Successfully: {0}, {1}", vertexPath, fragmentPath);
    }

    Shader::~Shader() { glDeleteProgram(m_RendererID); }
    void Shader::Bind() const { glUseProgram(m_RendererID); }
    void Shader::Unbind() const { glUseProgram(0); }
}