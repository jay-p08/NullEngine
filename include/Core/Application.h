#pragma once
#include "Core/Window.h"
#include <memory>

namespace NullEngine
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run(); // 메인 루프 실행
        void Close();

        inline static Application &Get() { return *s_Instance; }
        inline Window &GetWindow() { return *m_Window; }

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        static Application *s_Instance;
    };

    // 클라이언트 게임에서 이 함수를 구현하여 앱을 생성합니다.
    Application *CreateApplication();
}