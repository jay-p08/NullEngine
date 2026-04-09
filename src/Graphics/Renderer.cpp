#include "Graphics/Renderer.h"
#include <glad/glad.h>

namespace NullEngine
{
    void Renderer::Init()
    {
        // 블렌딩 설정 (나중에 투명도 있는 이미지를 위해 필요)
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::Clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::BeginScene() {}
    void Renderer::EndScene() {}

    void Renderer::Submit(const std::shared_ptr<Shader> &shader,
                          const std::shared_ptr<VertexArray> &vertexArray)
    {
        shader->Bind();
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}