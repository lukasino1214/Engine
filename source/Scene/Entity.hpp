#pragma once

#include <glm/glm.hpp>
#include <string>

#include "../Rendering/Model.h"
#include "../Rendering/Shader.hpp"

class Entity {
private:
    int n_id;

    std::string m_Name;

    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

    Model m_Model;

public:
    void setId(const int &id) { n_id = id; }
    int getId() const { return n_id; }

    void setName(const std::string &name) { m_Name = name; }
    std::string getName() const { return m_Name; }

    void setPosition(const glm::vec3 &position) { m_Position = position; }
    glm::vec3 getPosition() const { return m_Position; }

    void setRotation(const glm::vec3 &rotation) { m_Rotation = rotation; }
    glm::vec3 getRotation() const { return m_Rotation; }

    void setScale(const glm::vec3 &scale) { m_Scale = scale; }
    glm::vec3 getScale() const { return m_Scale; }

    void setModel(const std::string &path) {  m_Model.Load(path); }

    void Draw(Shader &shader) { m_Model.Draw(shader); }
};