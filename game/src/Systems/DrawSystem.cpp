#include "raylib.h"
#include "Systems/DrawSystem.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextureComponent.hpp"

void DrawSystem::Update()
{
    DoForEachComponent<TextureComponent>([this](TextureComponent& component)
        {
            // Draw spaceship
            TransformComponent* spaceship = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
            if (spaceship)
                DrawTextureV(component.Texture, spaceship->Position, WHITE);

            // Draw aliens
            TransformComponent* alien = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
            if (alien)
                DrawTextureV(component.Texture, alien->Position, WHITE);

        });
}