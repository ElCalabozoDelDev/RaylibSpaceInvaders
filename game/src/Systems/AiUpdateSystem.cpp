#include "raylib.h"
#include "Systems/AiUpdateSystem.hpp"
#include "Components/AiControllerComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextureComponent.hpp"
#include "Components/AlienComponent.hpp"
#include "Components/MysteryshipComponent.hpp"
#include "Components/ActiveStateComponent.hpp"
#include "Components/SpeedComponent.hpp"

void AiUpdateSystem::Update()
{
    bool changeDirection = false;

    // Comprueba si se necesita cambiar la dirección global
    CheckDirectionChange(changeDirection);

    // Mueve todos los aliens basándose en la dirección global
    MoveAliens(changeDirection);

    // Mueve la nave misteriosa
    MoveMysteryship();
}

void AiUpdateSystem::CheckDirectionChange(bool &changeDirection)
{
    DoForEachComponent<AlienComponent>([this, &changeDirection](AlienComponent &component)
                                              {
        TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
        if (!transform)
            return;
        

        TextureComponent* texture = ECSContainer.TryGetComponent<TextureComponent>(component.EntityId);
        if (!texture)
            return;
            
        AiControllerComponent* controller = ECSContainer.TryGetComponent<AiControllerComponent>(component.EntityId);
        if (!controller)
            return;

        if (component.Type < 4)
        {
            if (transform->Position.x + texture->Texture.width > GetScreenWidth() - 25 || transform->Position.x < 25)
            {
                changeDirection = true;
            }
        } });
}

void AiUpdateSystem::MoveAliens(bool changeDirection)
{
    DoForEachComponent<AlienComponent>([this, changeDirection](AlienComponent &component)
                                              {
        TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
        if (!transform)
            return;

        AiControllerComponent* controller = ECSContainer.TryGetComponent<AiControllerComponent>(component.EntityId);
        if (!controller)
            return;

        Vector2 move = {0, 0};

        if (changeDirection)
        {
            controller->Direction.x *= -1;
            move.y = 4;
        }

        move.x = controller->Direction.x;

        // Mueve los aliens
        transform->Position = Vector2Add(transform->Position, move); });
}

void AiUpdateSystem::MoveMysteryship()
{
    DoForEachComponent<MysteryshipComponent>([this](MysteryshipComponent &component)
                                              {
        TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
        if (!transform)
            return;

        TextureComponent* texture = ECSContainer.TryGetComponent<TextureComponent>(component.EntityId);
        if (!texture)
            return;

        ActiveStateComponent* active = ECSContainer.TryGetComponent<ActiveStateComponent>(component.EntityId);
        if (!active)
            return;
        SpeedComponent* speed = ECSContainer.TryGetComponent<SpeedComponent>(component.EntityId);
        if (!speed)
            return;

        if (active->Active)
        {
            transform->Position.x += speed->Speed;
            if (transform->Position.x > GetScreenWidth() - texture->Texture.width - 25 || transform->Position.x < 25)
            {
                active->Active = false;
            }
        } });
}
