#pragma once

#include <filesystem>
#include <string>

#include "Rendering/Texture.hpp"
#include "Base.hpp"
#include "TextureViewerPanel.hpp"

class ContentBrowserPanel {
    public:
        ContentBrowserPanel();

        void OnImGuiRender();
    private:
        std::filesystem::path m_CurrentDirectory;
        Ref<Texture> m_DirectoryIcon;
        Ref<Texture> m_FileIcon;
        Ref<TextureViewer> m_TextureViewer;
};