#include "raylib.h"
#include "Systems/DrawSystem.hpp"
#include "Components/SpaceshipComponent.hpp"
#include "Components/AlienComponent.hpp"
#include "Components/MysteryshipComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextureComponent.hpp"
#include "Components/ActiveStateComponent.hpp"
#include "Components/LaserComponent.hpp"
#include "Components/BlockComponent.hpp"
#include <iostream>

void DrawSystem::Update()
{
    DoForEachComponent<TextureComponent>([this](TextureComponent& component)
    {
        // Draw spaceship
        SpaceshipComponent* spaceship = ECSContainer.TryGetComponent<SpaceshipComponent>(component.EntityId);
        if (spaceship)
        {
            TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
            DrawTextureV(component.Texture, transform->Position, WHITE);
        }
        // Draw aliens
        AlienComponent* alien = ECSContainer.TryGetComponent<AlienComponent>(component.EntityId);
        if (alien)
        {
            TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
            DrawTextureV(component.Texture, transform->Position, WHITE);
        }
        // Draw mysteryship
        MysteryshipComponent* mysteryship = ECSContainer.TryGetComponent<MysteryshipComponent>(component.EntityId);
        if (mysteryship)
        {
            ActiveStateComponent* active = ECSContainer.TryGetComponent<ActiveStateComponent>(component.EntityId);
            if (active)
            {
                if (active->Active)
                {
                    TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
                    DrawTextureV(component.Texture, transform->Position, WHITE);
                }
            }
        }
    });

    // Draw lasers
    DoForEachComponent<TransformComponent>([this](TransformComponent& component)
    {
        LaserComponent* laser = ECSContainer.TryGetComponent<LaserComponent>(component.EntityId);
        if (laser)
        {
            ActiveStateComponent* active = ECSContainer.TryGetComponent<ActiveStateComponent>(component.EntityId);
            if (active && active->Active)
            {
                DrawRectangleV(component.Position, laser->Size, {243, 216, 63, 255});
            }
        }
    });

    // Draw blocks
    DoForEachComponent<TransformComponent>([this](TransformComponent& component)
    {
        BlockComponent* block = ECSContainer.TryGetComponent<BlockComponent>(component.EntityId);
        if (block)
            DrawRectangleV(component.Position, block->Size, block->Color);
    });
}