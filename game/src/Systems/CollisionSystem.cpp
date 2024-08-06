#include "raylib.h"
#include "Systems/CollisionSystem.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/LaserComponent.hpp"
#include "Components/SpaceshipComponent.hpp"
#include "Components/AlienComponent.hpp"
#include "Components/ObstacleComponent.hpp"
#include "Components/ActiveStateComponent.hpp"
#include "Components/MysteryshipComponent.hpp"
#include "Components/TextureComponent.hpp"
#include "Components/BlockComponent.hpp"
#include "Game.hpp"
#include <iostream>

void CollisionSystem::Update()
{
    CheckSpaceshipLasersCollisions();
}

void CollisionSystem::CheckSpaceshipLasersCollisions()
{
    // Lasers de la nave
    DoForEachComponent<LaserComponent>([this](LaserComponent &laser)
    {
        // Colisiones con los aliens
        DoForEachComponent<AlienComponent>([this, &laser](AlienComponent &alien)
        {
            CollisionComponent *laserCollision = ECSContainer.TryGetComponent<CollisionComponent>(laser.EntityId);
            if (!laserCollision)
                return;
            CollisionComponent *alienCollision = ECSContainer.TryGetComponent<CollisionComponent>(alien.EntityId);
            if (!alienCollision)
                return;

            if (CheckCollisionRecs(laserCollision->BoundingBox, alienCollision->BoundingBox))
            {
                Game::Instance()->AddScore(alien.Score());
                Game::Instance()->CheckHighScore();
                ECSContainer.RemoveEntity(laser.EntityId);
                ECSContainer.RemoveEntity(alien.EntityId);
                PlaySound(Game::Instance()->GetExplosionSound());
                if (GetAliensCount() == 0)
                {
                    Game::Instance()->GameOver();
                }
            }
        });

        // Colisiones con los obstáculos

        DoForEachComponent<BlockComponent>([this, &laser](BlockComponent &block)
        {
            CollisionComponent *laserCollision = ECSContainer.TryGetComponent<CollisionComponent>(laser.EntityId);
            if (!laserCollision)
                return;
            CollisionComponent *blockCollision = ECSContainer.TryGetComponent<CollisionComponent>(block.EntityId);
            if (!blockCollision)
                return;

            if (CheckCollisionRecs(laserCollision->BoundingBox, blockCollision->BoundingBox))
            {
                ECSContainer.RemoveEntity(laser.EntityId);
                ECSContainer.RemoveEntity(block.EntityId);
            }
        });

        // Colisiones con la nave misteriosa
        DoForEachComponent<MysteryshipComponent>([this, &laser](MysteryshipComponent &mysteryship)
        {
            CollisionComponent *laserCollision = ECSContainer.TryGetComponent<CollisionComponent>(laser.EntityId);
            if (!laserCollision)
                return;
            CollisionComponent *mysteryshipCollision = ECSContainer.TryGetComponent<CollisionComponent>(mysteryship.EntityId);
            if (!mysteryshipCollision)
                return;

            if (CheckCollisionRecs(laserCollision->BoundingBox, mysteryshipCollision->BoundingBox))
            {
                Game::Instance()->AddScore(mysteryship.Score);
                Game::Instance()->CheckHighScore();
                ECSContainer.RemoveEntity(laser.EntityId);
                ECSContainer.RemoveEntity(mysteryship.EntityId);
                PlaySound(Game::Instance()->GetExplosionSound());
            }
        });

    });
}

int CollisionSystem::GetAliensCount()
{
    int count = 0;
    DoForEachComponent<AlienComponent>([&count](AlienComponent &alien)
    {
        count++;
    });
    return count;
}