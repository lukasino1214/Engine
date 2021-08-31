#include "SceneSerializer.hpp"

#include <fstream>
#include <yaml-cpp/yaml.h>

SceneSerializer::SceneSerializer(Scene scene) : m_Scene(scene) {

}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
    return out;
}

static void SerializeEntity(YAML::Emitter& out, Entity entity) {
    // Entity
    out << YAML::BeginMap;
    out << YAML::Key << "Entity" << YAML::Value << entity.getID();

    // Data
    out << YAML::Key << "Data";
    out << YAML::BeginMap;
    out << YAML::Key << "Name" << YAML::Value << entity.getName();
    out << YAML::Key << "Model" << YAML::Value << entity.getModel();
    out << YAML::EndMap;

    // Transform
    out << YAML::Key << "Transform";
    out << YAML::BeginMap;
    out << YAML::Key << "Position" << YAML::Value << entity.getPosition();
    out << YAML::Key << "Rotation" << YAML::Value << entity.getRotation();
    out << YAML::Key << "Scale" << YAML::Value << entity.getScale();
    out << YAML::EndMap;

    out << YAML::EndMap;
}

void SceneSerializer::Serialize(std::string filepath) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Scene";
    out << YAML::Value << m_Scene.getName();
    out << YAML::Key << "Entities";
    out << YAML::Value << YAML::BeginSeq;
    std::vector<Entity> entities = m_Scene.getEntities();
    for(int i = 0; i < entities.size(); i++) {
        SerializeEntity(out, entities[i]);
    }
    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream fout(filepath);
    fout << out.c_str();
}

void SceneSerializer::SerializeRuntime(std::string filepath) {
    
}

void SceneSerializer::Deserialize(std::string filepath) {
    
}

void SceneSerializer::DeserializeRuntime(std::string filepath) {
    
}