#pragma once
#include "Graphics/OrthographicCamera.h"
#include "Graphics/Texture.h"
#include <glm/glm.hpp>
#include <memory>

namespace NullEngine
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera &camera);
        static void EndScene();

        // 1. 단색 사각형 그리기 (위치, 크기, 색상)
        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);

        // 2. 텍스처 사각형 그리기 (위치, 크기, 텍스처)
        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture);
    };
}