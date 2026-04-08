#include "Application.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace NullEngine
{

    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;

        // 윈도우 생성
        m_Window = std::make_unique<Window>(WindowProps("Null Engine", 1280, 720));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            // 1. 렌더링 준비 (배경색 설정 - 예: 어두운 파란색)
            glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // 2. 윈도우 업데이트 및 이벤트 폴링
            m_Window->OnUpdate();

            if (m_Window->ShouldClose())
            {
                m_Running = false;
            }
        }
    }
}