#pragma once

/*#include "Renderer.hpp"

class Texture {
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;

    public:
        Texture(const std::string& path);
        ~Texture();

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

        unsigned int GetRenderID() { return m_RendererID; }

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }
};*/

#include <glad/glad.h>
#include <string>

class Texture
{
public:
    Texture(unsigned int width, unsigned int height);
    Texture(const std::string& path);
    ~Texture();

    unsigned int GetWidth() const { return m_Width;  }
    unsigned int GetHeight() const { return m_Height; }
    unsigned int GetRendererID() const { return m_RendererID; }
    
    void SetData(void* data, unsigned int size);

    void Bind(unsigned int slot = 0) const;

    bool operator==(const Texture& other) const
    {
        return m_RendererID == ((Texture&)other).m_RendererID;
    }
private:
    std::string m_Path;
    unsigned int m_Width, m_Height;
    unsigned int m_RendererID;
    GLenum m_InternalFormat, m_DataFormat;
};