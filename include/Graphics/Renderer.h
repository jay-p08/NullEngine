#pragma once

#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"

namespace NullEngine
{
    class Renderer
    {
    public:
        static void Init();
        static void BeginScene(); // 카메라 설정 등을 여기서 처리할 예정
        static void EndScene();

        // 가장 기본적인 그리기 명령
        static void Submit(const std::shared_ptr<Shader> &shader,
                           const std::shared_ptr<VertexArray> &vertexArray);

        static void Clear(float r, float g, float b, float a);
    };
}