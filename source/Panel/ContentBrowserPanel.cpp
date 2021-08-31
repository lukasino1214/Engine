#include "ContentBrowserPanel.hpp"
#include "imgui.h"
#include <iostream>

static std::filesystem::path s_AssetPath = "resources";

ContentBrowserPanel::ContentBrowserPanel() : m_CurrentDirectory(s_AssetPath){
    m_DirectoryIcon = CreateRef<Texture>("folder.png");
    m_FileIcon = CreateRef<Texture>("file.png");
    m_TextureViewer = CreateRef<TextureViewer>();
}

void ContentBrowserPanel::OnImGuiRender() {
    ImGui::Begin("Content Browser");

    if(m_CurrentDirectory != std::filesystem::path(s_AssetPath)) {
        if(ImGui::Button("<-")) {
            m_CurrentDirectory = m_CurrentDirectory.parent_path();
        }
    }

    float padding = 16.0f;
    float thumbnailSize = 96;
    float cellsize = thumbnailSize + padding;

    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int)(panelWidth / cellsize);
    if (columnCount < 1)
        columnCount = 1;

    ImGui::Columns(columnCount, 0, false);

    for(auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory)) {
        const auto& path = directoryEntry.path();
        auto relativePath = std::filesystem::relative(path, s_AssetPath);
        std::string filenameString = relativePath.filename().string();

        Ref<Texture> icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;
        ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }, 0, { 0.0f, 0.0f, 0.0f, 0.0f });
        if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {

            if(path.extension() == ".png" || path.extension() == ".jpg") {
                m_TextureViewer->SetTexture(path.string());
                m_TextureViewer->SetTextureName(filenameString.c_str());
            }

            if(directoryEntry.is_directory())
                m_CurrentDirectory /= path.filename();
            }

        ImGui::TextWrapped(filenameString.c_str());

        ImGui::NextColumn();
    }

    ImGui::Columns(1);

    ImGui::End();

    if(m_TextureViewer->GetStatus()) {
        m_TextureViewer->OnImGuiRender();
    }
}