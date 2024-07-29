#pragma once

#include <unordered_map>
#include <vector>
#include "Entity.hpp"
#include "Components/Position.hpp"
#include "Components/Renderable.hpp"

class BlockSystem {
public:
    void CreateObstacle(std::vector<Entity>& entities,
                        std::unordered_map<Entity, Position>& positions,
                        std::unordered_map<Entity, Renderable>& renderables,
                        Vector2 position);
    void Update(std::vector<Entity>& entities, 
                std::unordered_map<Entity, Position>& positions, 
                std::unordered_map<Entity, Renderable>& renderables);
};