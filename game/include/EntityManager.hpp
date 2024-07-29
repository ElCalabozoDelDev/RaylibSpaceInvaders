#pragma once

#include "Entity.hpp"
#include <unordered_map>
#include <vector>
#include "Components/Position.hpp"
#include "Components/Renderable.hpp"
#include "Components/BlockComponent.hpp"

class EntityManager {
public:
    Entity CreateEntity();
    void DestroyEntity(Entity entity);
    template<typename T>
    void AddComponent(Entity entity, T component);
    template<typename T>
    T& GetComponent(Entity entity);
    // Otras funciones para manejar componentes
private:
    std::unordered_map<Entity, Position> positions;
    std::unordered_map<Entity, Renderable> sizes;
    std::unordered_map<Entity, BlockComponent> blockComponents;
    // Otros mapas para diferentes componentes
    Entity nextEntityId;
};