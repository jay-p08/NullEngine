#include "Core/Application.h"

#include "Core/Log.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Renderer.h"
#include "Graphics/OrthographicCamera.h"
#include "Graphics/Texture.h"
#include "Core/Timestep.h"

#include <GLFW/glfw3.h> // glfwGetTime()을 위해 필요할 수 있음

namespace NullEngine
{
    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;
        m_Window = std::make_unique<Window>("Null Engine Game", 1280, 720);
    }

    Application::~Application() {}

    void Application::Run()
    {
        Renderer::Init();

        // 1. 점 데이터에 UV 좌표(U, V) 추가! (총 5개씩)
        float vertices[] = {
            // 위치 (X, Y, Z)     // 텍스처 좌표 (U, V)
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 좌측 하단
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // 우측 하단
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // 우측 상단
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // 좌측 상단
        };

        uint32_t indices[] = {0, 1, 2, 2, 3, 0};

        auto va = std::make_shared<VertexArray>();
        auto vb = std::make_shared<VertexBuffer>(vertices, (uint32_t)sizeof(vertices));

        // 2. 엔진의 힘! 레이아웃에 Float2(aTexCoord)를 한 줄만 추가하면 알아서 계산됩니다.
        vb->SetLayout({
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float2, "aTexCoord"} // 추가!
        });

        va->AddVertexBuffer(vb);
        auto ib = std::make_shared<IndexBuffer>(indices, 6);
        va->SetIndexBuffer(ib);

        auto shader = std::make_shared<Shader>("assets/Shaders/Basic.vert", "assets/Shaders/Basic.frag");

        // 3. 텍스처 불러오기 (이미지 파일 이름은 본인이 저장한 이름으로 바꾸세요!)
        Texture2D texture("assets/Textures/logo.png");

        OrthographicCamera camera(-1.6f, 1.6f, -0.9f, 0.9f);
        float lastFrameTime = 0.0f;

        while (m_Running)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - lastFrameTime;
            lastFrameTime = time;

            Renderer::Clear(0.1f, 0.1f, 0.1f, 1.0f);

            float moveSpeed = 5.0f;
            if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_A) == GLFW_PRESS)
                camera.SetPosition({camera.GetPosition().x - moveSpeed * timestep, camera.GetPosition().y, 0.0f});
            if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_D) == GLFW_PRESS)
                camera.SetPosition({camera.GetPosition().x + moveSpeed * timestep, camera.GetPosition().y, 0.0f});

            Renderer::BeginScene();

            shader->Bind();
            shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

            // 4. 텍스처를 0번 슬롯에 바인딩하고 쉐이더에 알려주기
            texture.Bind(0);
            shader->SetInt("u_Texture", 0);

            Renderer::Submit(shader, va);
            Renderer::EndScene();

            if (m_Window->ShouldClose())
                m_Running = false;

            m_Window->OnUpdate();
        }
    }

    void Application::Close()
    {
        m_Running = false;
    }
}