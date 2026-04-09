#include "Graphics/Buffer.h"
#include <glad/glad.h>

static uint32_t ShaderDataTypeSize(NullEngine::ShaderDataType type)
{
    switch (type)
    {
    case NullEngine::ShaderDataType::Float:
        return 4;
    case NullEngine::ShaderDataType::Float2:
        return 4 * 2;
    case NullEngine::ShaderDataType::Float3:
        return 4 * 3;
    case NullEngine::ShaderDataType::Float4:
        return 4 * 4;
    }
    return 0;
}

namespace NullEngine
{
    // --- Layout 구현 ---
    BufferElement::BufferElement(ShaderDataType type, const std::string &name, bool normalized)
        : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

    uint32_t BufferElement::GetComponentCount() const
    {
        switch (Type)
        {
        case ShaderDataType::Float:
            return 1;
        case ShaderDataType::Float2:
            return 2;
        case ShaderDataType::Float3:
            return 3;
        case ShaderDataType::Float4:
            return 4;
        }
        return 0;
    }

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements)
        : m_Elements(elements)
    {
        uint32_t offset = 0;
        m_Stride = 0;
        for (auto &element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }

    // --- VertexBuffer 구현 ---
    VertexBuffer::VertexBuffer(float *vertices, uint32_t size)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_RendererID); }
    void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
    void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    // --- IndexBuffer 구현 ---
    IndexBuffer::IndexBuffer(uint32_t *indices, uint32_t count) : m_Count(count)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_RendererID); }
    void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }
    void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
}