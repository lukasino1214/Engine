#pragma once

#include <string>

#include "Scene.hpp"

class SceneSerializer {
    public:
        SceneSerializer(Scene scene);

        void Serialize(std::string filepath);
        void SerializeRuntime(std::string filepath);

        void Deserialize(std::string filepath);
        void DeserializeRuntime(std::string filepath);
    private:
        Scene m_Scene;
}