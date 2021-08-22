#pragma once

#include <glm/glm.hpp>
#include <string>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../Rendering/Model.h"
#include "../Rendering/Shader.hpp"

class Entity {
private:
    int m_ID;

    std::string m_Name;

    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

    Model m_Model;

public:
    void setID(const int &id) { m_ID = id; }
    int getID() const { return m_ID; }

    void setName(const std::string &name) { m_Name = name; }
    std::string getName() const { return m_Name; }

    void setPosition(const glm::vec3 &position) { m_Position = position; }
    glm::vec3 getPosition() const { return m_Position; }

    void setRotation(const glm::vec3 &rotation) { m_Rotation = rotation; }
    glm::vec3 getRotation() const { return m_Rotation; }

    void setScale(const glm::vec3 &scale) { m_Scale = scale; }
    glm::vec3 getScale() const { return m_Scale; }

    glm::mat4 getTransform() {
        /*glm::mat4 rotation = glm::mat4_cast(glm::quat(glm::radians(m_Rotation)));
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Position);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);
	    glm::mat4 model = translation * rotation * scale;
        return model;*/
        glm::mat4 rotation = glm::toMat4(glm::quat(m_Rotation)); 
        return glm::translate(glm::mat4(1.0f), m_Position) * rotation * glm::scale(glm::mat4(1.0f), m_Scale); }

    void setModel(const std::string &path) {  m_Model.Load(path); }

    void Draw(Shader &shader) { m_Model.Draw(shader); }
};