#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>

struct Log {
    Log();

    void Clear();
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);
    void Draw(const char* title);
};