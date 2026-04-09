#include "Core/Window.h"
#include "Core/Log.h"

namespace NullEngine
{
    Window::Window(const std::string &title, uint32_t width, uint32_t height)
    {
        if (!glfwInit())
        {
            NE_CORE_ERROR("Could not initialize GLFW!");
        }

        m_Window = glfwCreateWindow((int)width, (int)height, title.c_str(), nullptr, nullptr);

        if (!m_Window)
        {
            NE_CORE_ERROR("Could not create window!");
            glfwTerminate();
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            NE_CORE_ERROR("Failed to initialize GLAD");
        }
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
}