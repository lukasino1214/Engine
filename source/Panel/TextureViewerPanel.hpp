#include <string>
#include <iostream>
#include <filesystem>

#include "../Rendering/Texture.hpp"
#include "../Base.hpp"

class TextureViewer {
    public:
        TextureViewer();

        bool GetStatus() { return m_Open; }

        void TextureViewer::SetTexture(std::string path);
        void SetTextureName(std::string name) { m_Name = name; }
        std::string GetTextureName() { return m_Name; }

        void OnImGuiRender();

    private:
        std::string m_Path;
        Ref<Texture> m_Texture;
        bool m_Open;
        std::string m_Name;
};