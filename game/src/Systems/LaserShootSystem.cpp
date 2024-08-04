#include "raylib.h"
#include "Systems/LaserShootSystem.hpp"
#include "Components/LaserComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/SpeedComponent.hpp"
#include "Components/PlayerInputComponent.hpp"
#include "Components/ActiveStateComponent.hpp"
#include <iostream>

void LaserShootSystem::Update()
{
    DoForEachComponent<PlayerInputComponent>([this](PlayerInputComponent &component)
        {
            if (component.Shoot)
            {
                uint64_t laserId = ECSContainer.GetNewEntity();
                TransformComponent* playerTransform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);

                if (!playerTransform)
                    return;

                ECSContainer.GetComponent<TransformComponent>(laserId)->Position = {playerTransform->Position.x + 22, playerTransform->Position.y}; // Ajustar posición del láser
                ECSContainer.GetComponent<LaserComponent>(laserId)->LastShootTime = GetTime();
                ECSContainer.GetComponent<LaserComponent>(laserId)->ShootCooldown = 0.5; // Ejemplo de cooldown
                ECSContainer.GetComponent<SpeedComponent>(laserId)->Speed = 3; // Velocidad del láser
                ECSContainer.GetComponent<ActiveStateComponent>(laserId)->Active = true; // Activar el láser
            }
        });

    DoForEachComponent<LaserComponent>([this](LaserComponent &component)
        {
            TransformComponent* transform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
            if (!transform)
                return;

            SpeedComponent* speed = ECSContainer.TryGetComponent<SpeedComponent>(component.EntityId);
            if (!speed)
                return;

            transform->Position.y -= speed->Speed;

            if (transform->Position.y < 0 || transform->Position.y > GetScreenHeight())
            {
                ECSContainer.RemoveEntity(component.EntityId);
            }
        });
}