#pragma once

#include "Window.h"
#include <memory>

namespace NullEngine {

    class Application {
    public:
        Application();
        virtual ~Application();

        // 엔진 실행
        void Run();

        // 전역에서 Application 객체에 접근하기 위한 싱글톤
        static Application& Get() { return *s_Instance; }
        
        Window& GetWindow() { return *m_Window; }

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

        static Application* s_Instance;
    };

    // 사용자가 정의할 앱 생성 함수 (EntryPoint에서 호출)
    Application* CreateApplication();
}