#include "Graphics/Texture.h"
#include "Core/Log.h"
#include <glad/glad.h>
#include <stb_image.h>

namespace NullEngine
{
    Texture2D::Texture2D(const std::string &path)
        : m_Path(path)
    {

        int width, height, channels;
        // OpenGL은 이미지의 Y축(위아래)이 반대라서 뒤집어서 읽어야 합니다.
        stbi_set_flip_vertically_on_load(1);

        stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if (data)
        {
            m_Width = width;
            m_Height = height;

            GLenum internalFormat = 0, dataFormat = 0;
            if (channels == 4)
            { // 투명도(Alpha)가 있는 PNG
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
            }
            else if (channels == 3)
            { // 투명도가 없는 JPG 등
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
            }

            glGenTextures(1, &m_RendererID);
            glBindTexture(GL_TEXTURE_2D, m_RendererID);

            // 텍스처 확대/축소 시 어떻게 보일지 설정 (도트 게임 느낌을 원하면 GL_NEAREST)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data); // GPU로 보냈으니 CPU 메모리에서는 삭제
        }
        else
        {
            NE_CORE_ERROR("Failed to load image! Path: {0}", path);
        }
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture2D::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }
}