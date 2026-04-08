#pragma once

#include <string>
#include <iostream>

namespace NullEngine
{

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string &title = "Null Engine",
                    unsigned int width = 1280,
                    unsigned int height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    class Window
    {
    public:
        Window(const WindowProps &props);
        virtual ~Window();

        void OnUpdate();

        unsigned int GetWidth() const { return m_Data.Width; }
        unsigned int GetHeight() const { return m_Data.Height; }

        bool ShouldClose() const; // 창이 닫혀야 하는지 확인

    private:
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
        };

        WindowData m_Data;
        // 여기에 나중에 GLFWwindow* m_Window; 가 들어갈 예정입니다.
    };

}