#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace NullEngine
{

    // GLFW 에러 콜백 (문제가 생기면 로그를 찍음)
    static void GLFWErrorCallback(int error, const char *description)
    {
        spdlog::error("GLFW Error ({0}): {1}", error, description);
    }

    struct WindowInternalData
    {
        GLFWwindow *NativeWindow;
        // 향후 이벤트 콜백 등을 여기에 추가
    };

    static WindowInternalData *s_InternalData = nullptr;

    Window::Window(const WindowProps &props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        // 1. GLFW 초기화
        if (!glfwInit())
        {
            spdlog::critical("Could not initialize GLFW!");
            return;
        }

        glfwSetErrorCallback(GLFWErrorCallback);

        // 2. OpenGL 버전 설정 (4.5 Core Profile 권장)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // 3. 창 생성
        s_InternalData = new WindowInternalData();
        s_InternalData->NativeWindow = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

        if (!s_InternalData->NativeWindow)
        {
            spdlog::critical("Failed to create GLFW window!");
            return;
        }

        // 4. OpenGL 컨텍스트를 현재 창으로 설정
        glfwMakeContextCurrent(s_InternalData->NativeWindow);

        // 5. GLAD 초기화 (OpenGL 함수 로드)
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            spdlog::critical("Failed to initialize GLAD!");
            return;
        }

        spdlog::info("Window Created: {0} ({1}, {2})", props.Title, props.Width, props.Height);

        // VSync 활성화 (화면 찢어짐 방지)
        glfwSwapInterval(1);
    }

    Window::~Window()
    {
        glfwDestroyWindow(s_InternalData->NativeWindow);
        glfwTerminate();
        delete s_InternalData;
    }

    void Window::OnUpdate()
    {
        // 이벤트(키보드, 마우스 등) 처리
        glfwPollEvents();
        // 버퍼 스왑 (그려진 내용을 화면에 출력)
        glfwSwapBuffers(s_InternalData->NativeWindow);
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(s_InternalData->NativeWindow);
    }
}