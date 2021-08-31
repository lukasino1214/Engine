#include "TextureViewerPanel.hpp"
#include "imgui.h"

TextureViewer::TextureViewer() {
    m_Path = "";
    m_Open = false;
}

void TextureViewer::SetTexture(std::string path) {
    m_Texture = CreateRef<Texture>(path);
    m_Open = true;
}

void TextureViewer::OnImGuiRender() {
    ImGui::Begin("Texture viewer", &m_Open);
    ImGui::SetWindowSize({ (float)m_Texture->GetWidth()/2 + 16.0f , (float)m_Texture->GetHeight()/2 + 72.0f });
    ImGui::Text("Name of texture: %s", m_Name);
    ImGui::Text("Image Width: %i , Height: %i", (int)m_Texture->GetWidth(), (int)m_Texture->GetHeight());
    ImGui::Image((ImTextureID)m_Texture->GetRendererID(), { (float)m_Texture->GetWidth()/2, (float)m_Texture->GetHeight()/2 }, { 0, 1 }, { 1, 0 });
    ImGui::End();
}