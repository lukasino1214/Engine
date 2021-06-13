#pragma once

// imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// glad
#include <glad/glad.h>

// glfw
#include <glfw/glfw3.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

// // assimp
// #include <assimp/scene.h>

// std
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <stdio.h>

#include "Rendering/Renderer.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexArray.h"
#include "Rendering/VertexBufferLayout.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Rendering/Camera.h"
#include "Rendering/model.h"

#include "GUI/GUI.h"
#include "GUI/Log.h"
#include "GUI/Viewport.h"