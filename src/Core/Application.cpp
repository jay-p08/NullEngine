#include "Application.h"

#include "Graphics/Shader.h"
#include "Graphics/Buffer.h"

#include <glad/glad.h>
#include <memory>

namespace NullEngine
{
    Application* Application::s_Instance = nullptr;

    // 렌더링에 필요한 객체들 (나중에 렌더러 클래스로 분리할 예정)
    static std::unique_ptr<Shader> s_Shader;
    static std::unique_ptr<VertexBuffer> s_VB;
    static uint32_t s_VAO; // Vertex Array Object

    Application::Application()
    {
        s_Instance = this;
        m_Window = std::make_unique<Window>(WindowProps("Null Engine", 1280, 720));

        // 1. 삼각형 데이터 (NDC 좌표계: -1.0 ~ 1.0)
        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f, // 좌측 하단
            0.5f, -0.5f, 0.0f,  // 우측 하단
            0.0f, 0.5f, 0.0f    // 중앙 상단
        };

        // 2. VAO 생성 (데이터의 해석 방법을 저장하는 객체)
        glCreateVertexArrays(1, &s_VAO);
        glBindVertexArray(s_VAO);

        // 3. VBO 생성 및 데이터 할당
        s_VB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

        // 4. Vertex Attribute 설정 (중요: 데이터가 어떻게 구성되어 있는지 GPU에 알려줌)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0);

        // 5. Shader 생성 (아까 만든 파일 경로 입력)
        s_Shader = std::make_unique<Shader>("assets/Shaders/Basic.vert", "assets/Shaders/Basic.frag");
    }
    Application::~Application()
    {
        // 소멸자 내용이 비어있더라도 정의는 반드시 있어야 합니다!
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // 6. 그리기!
            s_Shader->Bind();
            glBindVertexArray(s_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            m_Window->OnUpdate();
            if (m_Window->ShouldClose())
                m_Running = false;
        }
    }
}