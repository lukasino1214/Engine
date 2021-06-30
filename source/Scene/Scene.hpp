#pragma once

#include "Entity.hpp"
#include <vector>
//#include <string>

class Scene {
    private:
        std::string m_Name;
        std::vector<Entity> m_Entities;

    public:

        void setName(const std::string &name) { m_Name = name; }
        std::string getName() const { return m_Name; }

        std::vector<Entity> setEntities(const std::vector<Entity> &entities) { m_Entities = entities; }
        std::vector<Entity> getEntities() const { return m_Entities; }
        void addEntity(Entity entityla) { m_Entities.push_back(entityla); }

        void Render(Shader &shader) {
            for (size_t i = 0; i < m_Entities.size(); i++) {
                m_Entities[i].Draw(shader);
        }
    }
};