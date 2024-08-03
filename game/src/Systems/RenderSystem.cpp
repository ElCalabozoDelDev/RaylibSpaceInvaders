#include "Systems/RenderSystem.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/BlockComponent.hpp"

void RenderSystem::Update()
{
    DoForEachComponent<TransformComponent>([this](TransformComponent& component)
        {
            BlockComponent* block = ECSContainer.TryGetComponent<BlockComponent>(component.EntityId);
            if (!block)
                return;

            DrawRectangleV(component.Position, block->Size, block->Color);
        });
}