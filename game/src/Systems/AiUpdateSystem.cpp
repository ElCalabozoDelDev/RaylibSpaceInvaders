#include "raylib.h"
#include "Systems/AiUpdateSystem.hpp"
#include "Components/AiControllerComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextureComponent.hpp"

void AiUpdateSystem::Update()
{
    bool changeDirection = false;
    int globalDirection = 1; // Puede ser 1 o -1 dependiendo de la dirección actual

    // Comprueba si se necesita cambiar la dirección global
    CheckDirectionChange(changeDirection, globalDirection);

    // Mueve todos los aliens basándose en la dirección global
    MoveAliens(changeDirection, globalDirection);
}

void AiUpdateSystem::CheckDirectionChange(bool &changeDirection, int &globalDirection)
{
    DoForEachComponent<AiControllerComponent>([this, &changeDirection, &globalDirection](AiControllerComponent &component)
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
                globalDirection = -1;
            }
            if (transform->Position.x < 25)
            {
                changeDirection = true;
                globalDirection = 1;
            }
        } });
}

void AiUpdateSystem::MoveAliens(bool changeDirection, int globalDirection)
{
    DoForEachComponent<AiControllerComponent>([this, changeDirection, globalDirection](AiControllerComponent &component)
                                              {
        TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
        if (!transform)
            return;

        Vector2 move = {0, 0};

        if (changeDirection)
        {
            component.Direction = globalDirection;
            move.y = 4;
        }

        move.x = component.Direction;

        // Mueve los aliens
        transform->Position = Vector2Add(transform->Position, move); });
}
