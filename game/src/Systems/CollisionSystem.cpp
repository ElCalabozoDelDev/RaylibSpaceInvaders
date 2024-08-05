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
#include "Game.hpp"

void CollisionSystem::Update()
{
    CheckCollisions();
}

void CollisionSystem::CheckCollisions()
{
    // Colisiones entre láseres de la nave y alienígenas
    DoForEachComponent<LaserComponent>([this](LaserComponent &laser)
    {
        if (!ECSContainer.TryGetComponent<ActiveStateComponent>(laser.EntityId)->Active)
            return;

        TransformComponent* laserTransform = ECSContainer.TryGetComponent<TransformComponent>(laser.EntityId);
        CollisionComponent* laserCollision = ECSContainer.TryGetComponent<CollisionComponent>(laser.EntityId);

        if (!laserTransform || !laserCollision)
            return;

        DoForEachComponent<AlienComponent>([this, &laserTransform, &laserCollision, &laser](AlienComponent &alien)
        {
            TransformComponent* alienTransform = ECSContainer.TryGetComponent<TransformComponent>(alien.EntityId);
            CollisionComponent* alienCollision = ECSContainer.TryGetComponent<CollisionComponent>(alien.EntityId);

            if (!alienTransform || !alienCollision)
                return;

            if (CheckCollisionRecs(laserCollision->BoundingBox, alienCollision->BoundingBox))
            {
                PlaySound(Game::Instance()->GetExplosionSound());
                // Handle score, game logic, etc.
                
                ECSContainer.RemoveEntity(laser.EntityId);
                ECSContainer.RemoveEntity(alien.EntityId);
                // Verificar si hay que actualizar el puntaje
                Game::Instance()->CheckHighScore();
                if (Game::Instance()->GetAliensCount() == 0)
                {
                    Game::Instance()->GameOver();
                }
            }
        });

        // Colisiones entre láseres y obstáculos
        DoForEachComponent<ObstacleComponent>([this, &laser, laserTransform, laserCollision](ObstacleComponent &obstacle)
        {
            for (int i = 0; i < obstacle.Grid.size(); i++)
            {
                for (int j = 0; j < obstacle.Grid[i].size(); j++)
                {
                    if (obstacle.Grid[i][j] == 1)
                    {
                        Rectangle blockRect = {
                            laserTransform->Position.x + j * 3,
                            laserTransform->Position.y + i * 3,
                            3,
                            3
                        };
                        if (CheckCollisionRecs(laserCollision->BoundingBox, blockRect))
                        {
                            obstacle.Grid[i][j] = 0; // Remove block
                            ECSContainer.RemoveEntity(laser.EntityId);
                            break;
                        }
                    }
                }
            }
        });

        // Colisiones entre láseres y la nave espacial misteriosa
        DoForEachComponent<MysteryshipComponent>([this, &laserTransform, &laserCollision, &laser](MysteryshipComponent &mysteryShip)
        {
            TransformComponent* mysteryTransform = ECSContainer.TryGetComponent<TransformComponent>(mysteryShip.EntityId);
            CollisionComponent* mysteryCollision = ECSContainer.TryGetComponent<CollisionComponent>(mysteryShip.EntityId);

            if (mysteryTransform && mysteryCollision && CheckCollisionRecs(laserCollision->BoundingBox, mysteryCollision->BoundingBox))
            {
                PlaySound(Game::Instance()->GetExplosionSound());
                // Handle score, game logic, etc.
                ECSContainer.RemoveEntity(mysteryShip.EntityId);
                ECSContainer.RemoveEntity(laser.EntityId);
                Game::Instance()->CheckHighScore();
            }
        });
    });

    // Colisiones entre láseres de alienígenas y la nave del jugador
    DoForEachComponent<LaserComponent>([this](LaserComponent &laser)
    {
        if (!ECSContainer.TryGetComponent<ActiveStateComponent>(laser.EntityId)->Active)
            return;

        TransformComponent* laserTransform = ECSContainer.TryGetComponent<TransformComponent>(laser.EntityId);
        CollisionComponent* laserCollision = ECSContainer.TryGetComponent<CollisionComponent>(laser.EntityId);

        if (!laserTransform || !laserCollision)
            return;

        DoForEachComponent<SpaceshipComponent>([this, &laserTransform, &laserCollision, &laser](SpaceshipComponent &spaceship)
        {
            TransformComponent* spaceshipTransform = ECSContainer.TryGetComponent<TransformComponent>(spaceship.EntityId);
            CollisionComponent* spaceshipCollision = ECSContainer.TryGetComponent<CollisionComponent>(spaceship.EntityId);

            if (spaceshipTransform && spaceshipCollision && CheckCollisionRecs(laserCollision->BoundingBox, spaceshipCollision->BoundingBox))
            {
                Game::Instance()->DecreaseLives();
                if (Game::Instance()->GetLives() == 0)
                {
                    Game::Instance()->GameOver();
                }

                ECSContainer.RemoveEntity(laser.EntityId);
            }
        });

        // Colisiones entre láseres de alienígenas y obstáculos
        DoForEachComponent<ObstacleComponent>([this, &laser, laserTransform, laserCollision](ObstacleComponent &obstacle)
        {
            for (int i = 0; i < obstacle.Grid.size(); i++)
            {
                for (int j = 0; j < obstacle.Grid[i].size(); j++)
                {
                    if (obstacle.Grid[i][j] == 1)
                    {
                        Rectangle blockRect = {
                            laserTransform->Position.x + j * 3,
                            laserTransform->Position.y + i * 3,
                            3,
                            3
                        };
                        if (CheckCollisionRecs(laserCollision->BoundingBox, blockRect))
                        {
                            obstacle.Grid[i][j] = 0; // Remove block
                            ECSContainer.RemoveEntity(laser.EntityId);
                            break;
                        }
                    }
                }
            }
        });
    });

    // Colisiones entre alienígenas y obstáculos
    DoForEachComponent<AlienComponent>([this](AlienComponent &alien)
    {
        TransformComponent* alienTransform = ECSContainer.TryGetComponent<TransformComponent>(alien.EntityId);
        CollisionComponent* alienCollision = ECSContainer.TryGetComponent<CollisionComponent>(alien.EntityId);

        if (!alienTransform || !alienCollision)
            return;

        DoForEachComponent<ObstacleComponent>([this, &alien, alienTransform, alienCollision](ObstacleComponent &obstacle)
        {
            for (int i = 0; i < obstacle.Grid.size(); i++)
            {
                for (int j = 0; j < obstacle.Grid[i].size(); j++)
                {
                    if (obstacle.Grid[i][j] == 1)
                    {
                        Rectangle blockRect = {
                            alienTransform->Position.x + j * 3,
                            alienTransform->Position.y + i * 3,
                            3,
                            3
                        };
                        if (CheckCollisionRecs(alienCollision->BoundingBox, blockRect))
                        {
                            obstacle.Grid[i][j] = 0; // Remove block
                        }
                    }
                }
            }
        });

        // Colisiones entre alienígenas y la nave del jugador
        DoForEachComponent<SpaceshipComponent>([this, &alienTransform, &alienCollision](SpaceshipComponent &spaceship)
        {
            TransformComponent* spaceshipTransform = ECSContainer.TryGetComponent<TransformComponent>(spaceship.EntityId);
            CollisionComponent* spaceshipCollision = ECSContainer.TryGetComponent<CollisionComponent>(spaceship.EntityId);

            if (spaceshipTransform && spaceshipCollision && CheckCollisionRecs(alienCollision->BoundingBox, spaceshipCollision->BoundingBox))
            {
                Game::Instance()->GameOver();
            }
        });
    });
}