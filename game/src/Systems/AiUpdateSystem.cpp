#include "raylib.h"
#include "Systems/AiUpdateSystem.hpp"
#include "Components/AiControllerComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextureComponent.hpp"

void AiUpdateSystem::Update()
{
    bool changeDirection = false;

    // Comprueba si se necesita cambiar la dirección global
    CheckDirectionChange(changeDirection);

    // Mueve todos los aliens basándose en la dirección global
    MoveAliens(changeDirection);
}

void AiUpdateSystem::CheckDirectionChange(bool &changeDirection)
{
    DoForEachComponent<AiControllerComponent>([this, &changeDirection](AiControllerComponent &component)
                                              {
        TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
        if (!transform)
            return;

        TextureComponent* texture = ECSContainer.TryGetComponent<TextureComponent>(component.EntityId);
        if (!texture)
            return;

        if (component.Type < 4)
        {
            if (transform->Position.x + texture->Texture.width > GetScreenWidth() - 25)
            {
                changeDirection = true;
            }
            if (transform->Position.x < 25)
            {
                changeDirection = true;
            }
        } });
}

void AiUpdateSystem::MoveAliens(bool changeDirection)
{
    DoForEachComponent<AiControllerComponent>([this, changeDirection](AiControllerComponent &component)
                                              {
        TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
        if (!transform)
            return;

        Vector2 move = {0, 0};

        if (changeDirection)
        {
            component.Direction.x *= -1;
            move.y = 4;
        }

        move.x = component.Direction.x;

        // Mueve los aliens
        transform->Position = Vector2Add(transform->Position, move); });
}
