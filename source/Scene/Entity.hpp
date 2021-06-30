#pragma once

#include <glm/glm.hpp>
#include <string>

#include "../Rendering/Model.h"
#include "../Rendering/Shader.hpp"

class Entity {
private:
    std::string name;

    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

    Model m_Model;

public:
    void setPosition(const glm::vec3 &position) { /*position = m_Position;*/ m_Position = position; }
    glm::vec3 getPosition() const { return m_Position; }

    void setRotation(const glm::vec3 &rotation) { /*rotation = m_Rotation;*/ m_Rotation = rotation; }
    glm::vec3 getRotation() const { return m_Rotation; }

    void setScale(const glm::vec3 &scale) { /*scale = m_Scale;*/ m_Scale = scale; }
    glm::vec3 getScale() const { return m_Scale; }

    void setModel(const std::string &path) {  m_Model.Load(path); }

    void Draw(Shader &shader) { m_Model.Draw(shader); }
};