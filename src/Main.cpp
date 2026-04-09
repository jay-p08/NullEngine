#include "Core/Application.h"
#include "Core/Log.h"

int main()
{
    NullEngine::Log::Init();
    NE_CORE_INFO("Engine Started!");

    auto app = new NullEngine::Application();
    app->Run();
    delete app;

    return 0;
}