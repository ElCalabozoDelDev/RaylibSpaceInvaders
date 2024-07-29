#include "Systems/RenderSystem.hpp"
#include <raylib.h>

void RenderSystem::Update(std::vector<Entity>& entities, 
                          std::unordered_map<Entity, Position>& positions, 
                          std::unordered_map<Entity, Renderable>& renderables) {
    for (auto& entity : entities) {
        if (positions.find(entity) != positions.end() && 
            renderables.find(entity) != renderables.end()) {
            auto& position = positions[entity];
            auto& renderable = renderables[entity];
            DrawRectangleV(position.position, renderable.size, renderable.color);
        }
    }
}
