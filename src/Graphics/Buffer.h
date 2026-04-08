#pragma once
#include <cstdint>

namespace NullEngine
{

    class VertexBuffer
    {
    public:
        VertexBuffer(float *vertices, uint32_t size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_RendererID;
    };

    // IndexBuffer도 비슷한 구조로 구현하게 됩니다.
}