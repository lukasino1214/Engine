#include "Viewport.h"
    
int xpos, ypos;

void Viewport::Window(GLFWwindow* window) {
    ImGui::Begin("Viewport");
    ImGui::Text("Work in progress");

    auto ViewportWindowPos = ImGui::GetWindowPos();
    auto ViewportWindowSize = ImGui::GetWindowSize();

    glfwGetWindowPos(window, &xpos, &ypos);

    double position_x = (ViewportWindowPos.x + ViewportWindowSize.x * 0.5) - xpos;
    double position_y = (ViewportWindowPos.y + ViewportWindowSize.y * 0.5) - ypos;
    
    glfwSetCursorPos(window, position_x, position_y);
    ImGui::End();
}