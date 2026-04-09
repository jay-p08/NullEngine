#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace NullEngine
{
    class Window
    {
    public:
        Window(const std::string &title, uint32_t width, uint32_t height);
        ~Window();

        bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }
        void OnUpdate();

        GLFWwindow *GetNativeWindow() const { return m_Window; }

    private:
        GLFWwindow *m_Window;
    };
}