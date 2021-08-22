#pragma once

#include "Entity.hpp"
#include <vector>
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include<glm/common.hpp>
//#include <string>

class Scene {
    private:
        std::string m_Name;
        std::vector<Entity> m_Entities;
        int m_MaxID;

    public:

        void setName(const std::string &name) { m_Name = name; }
        std::string getName() const { return m_Name; }

        void setEntities(const std::vector<Entity> &entities) { 
            m_Entities = entities; 
            for(int i = 0; i < entities.size(); i++) {
                m_Entities[i].setID(i);
                m_MaxID = i;
            }
        }

        int getMaxID() { return m_MaxID; }

        std::vector<Entity> getEntities() const { return m_Entities; }
        void addEntity(Entity entity) { m_Entities.push_back(entity); }

        void Render(Shader &shader) {

            for (size_t i = 0; i < m_Entities.size(); i++) {
                shader.Bind();

                /*glm::mat4 model = glm::mat4(1.0f);
                glm::mat4 translate = glm::mat4(1.0f);
                glm::mat4 scale = glm::mat4(1.0f);
                glm::mat4 rotation = glm::mat4(1.0f);
                
                translate = glm::translate(translate, m_Entities[i].getPosition());

                rotation = glm::rotate(rotation, glm::radians(m_Entities[i].getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
                rotation = glm::rotate(rotation, glm::radians(m_Entities[i].getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
                rotation = glm::rotate(rotation, glm::radians(m_Entities[i].getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
                
                scale = glm::scale(glm::mat4(1.0f), m_Entities[i].getScale());

                model = scale * translate * rotation;*/

                glm::mat4 rotation = glm::mat4_cast(glm::quat(glm::radians(m_Entities[i].getRotation())));
                glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Entities[i].getPosition());
                glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Entities[i].getScale());
			    glm::mat4 model = translation * rotation * scale;

                int id = m_Entities[i].getID();

                shader.SetUniformMat4f("model", model);
                shader.SetUniform1i("EntityID", id);
                m_Entities[i].Draw(shader);
                shader.Unbind();
            }
        }
};