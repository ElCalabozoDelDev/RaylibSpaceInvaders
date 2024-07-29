#pragma once

#include "Entity.hpp"
#include "Components/Position.hpp"
#include "Components/Renderable.hpp"
#include <unordered_map>
#include <vector>

class CollisionSystem {
public:
    void Update(const std::vector<Entity>& entities, 
                const std::unordered_map<Entity, Position>& positions, 
                const std::unordered_map<Entity, Renderable>& renderable);
};
