#include "raylib.h"
#include "Systems/DrawSystem.hpp"
#include "Systems/TransformManager.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/SpaceshipComponent.hpp"

void DrawSystem::Update()
{
    DoForEachComponent<TransformComponent>([this](TransformComponent& component)
        {
            // TransformManager::PushTransformComponent(component, ECSContainer);
            SpaceshipComponent* spaceship = ECSContainer.TryGetComponent<SpaceshipComponent>(component.EntityId);
            if (spaceship)
                DrawTextureV(spaceship->Texture, component.Position, WHITE);

            // TransformManager::PopTransformComponent(component, ECSContainer);
        });
}