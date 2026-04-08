#include "Buffer.h"
#include <glad/glad.h>

namespace NullEngine {

    // --- VertexBuffer ---
    VertexBuffer::VertexBuffer(float* vertices, uint32_t size) {
        // GPU에 버퍼 식별자 생성
        glCreateBuffers(1, &m_RendererID);
        // 버퍼 바인딩
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        // 데이터 업로드 (Static Draw: 데이터가 자주 바뀌지 않을 때 사용)
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}