#include "Core/Application.h"

int main()
{
    // 엔진 객체 생성
    auto app = new NullEngine::Application();

    // 엔진 가동
    app->Run();

    // 종료 시 메모리 해제
    delete app;

    return 0;
}