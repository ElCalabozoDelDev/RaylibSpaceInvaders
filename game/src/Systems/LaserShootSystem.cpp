#include "raylib.h"
#include "Systems/LaserShootSystem.hpp"
#include "Components/LaserComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/SpeedComponent.hpp"
#include "Components/PlayerInputComponent.hpp"
#include "Components/ActiveStateComponent.hpp"
#include "Components/SpaceshipComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/LaserComponent.hpp"
#include "Components/ShootComponent.hpp"
#include <iostream>
#include "Game.hpp"

void LaserShootSystem::Update()
{
    DoForEachComponent<PlayerInputComponent>([this](PlayerInputComponent &component)
        {
            ShootComponent* shoot = ECSContainer.TryGetComponent<ShootComponent>(component.EntityId);
            if (!shoot)
                return;
            float currentTime = GetTime();
            if (shoot->Shoot && (currentTime - shoot->LastShootTime >= shoot->ShootCooldown))
            {
                uint64_t laserId = ECSContainer.GetNewEntity();
                TransformComponent* playerTransform = ECSContainer.TryGetComponent<TransformComponent>(component.EntityId);
                if (!playerTransform)
                    return;
                    
                ECSContainer.GetComponent<SpeedComponent>(laserId)->Speed = 3; // Velocidad del láser
                ECSContainer.GetComponent<ActiveStateComponent>(laserId)->Active = true; // Activar el láser
                auto &size = ECSContainer.GetComponent<LaserComponent>(laserId)->Size; // Añadir el componente vacío
                auto& pos = ECSContainer.GetComponent<TransformComponent>(laserId)->Position = {playerTransform->Position.x + 22, playerTransform->Position.y}; // Ajustar posición del láser
                auto& bbox = ECSContainer.GetComponent<CollisionComponent>(laserId)->BoundingBox; // Ajustar bounding box
                bbox.x = pos.x;
                bbox.y = pos.y;
                bbox.width = size.x;
                bbox.height = size.y;
                shoot->LastShootTime = currentTime;
                PlaySound(Game::Instance()->GetShootSound());
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
            
            CollisionComponent* collision = ECSContainer.TryGetComponent<CollisionComponent>(component.EntityId);
            if (!collision)
                return;

            transform->Position.y -= speed->Speed;

            if (transform->Position.y < 0 || transform->Position.y > GetScreenHeight())
            {
                ECSContainer.RemoveEntity(component.EntityId);
            }
            // Actualizar bounding box
            collision->BoundingBox.x = transform->Position.x;
            collision->BoundingBox.y = transform->Position.y;
        });
}