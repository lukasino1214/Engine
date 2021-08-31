#pragma once

// imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuizmo.h"

// glad
#include <glad/glad.h>

// glfw
//#include <glfw/glfw3.h>
#include <GLFW/glfw3.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

// // assimp
// #include <assimp/scene.hpp>

// std
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <stdio.h>

#include "Rendering/Renderer.hpp"
#include "Rendering/VertexBuffer.hpp"
#include "Rendering/IndexBuffer.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/VertexBufferLayout.hpp"
#include "Rendering/Shader.hpp"
//#include "Rendering/Texture.hpp"
#include "Rendering/Camera.hpp"
#include "Rendering/Framebuffer.hpp"
//#include "Rendering/model.h"

/*class#include "GUI/GUI.hpp"
#include "GUI/Log.hpp"
#include "GUI/Viewport.hpp"*/

//#include "Scene/Entity.hpp"
#include "Scene/SceneSerializer.hpp"

#include "Panel/ContentBrowserPanel.hpp"