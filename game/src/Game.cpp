#include "Game.hpp"
#include "raylib.h"
#include "patch.hpp"
#include <string>
#include "Components/PlayerInputComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextureComponent.hpp"
#include "Components/AiControllerComponent.hpp"
#include "Components/SpaceshipComponent.hpp"
#include "Components/AlienComponent.hpp"
#include "Components/MysteryshipComponent.hpp"
#include "Components/BlockComponent.hpp"
#include "Components/ObstacleComponent.hpp"
#include "Components/ActiveStateComponent.hpp"
#include "Systems/DrawSystem.hpp"
#include "Systems/PlayerUpdateSystem.hpp"
#include "Systems/AiUpdateSystem.hpp"
#include "Systems/MysteryshipSpawnSystem.hpp"
#include "Systems/RenderSystem.hpp"

#define _ECS_IMPLEMENTATION
#include "ecs.h"

Game *Game::s_pInstance = 0;
ECS ecs;

Game::Game()
{
    RegisterComponents();
    RegisterSystems();
    CreateEntities();
}

Game::~Game()
{
}

void Game::RegisterComponents()
{
    ecs.RegisterComponent<PlayerInputComponent>();
    ecs.RegisterComponent<TransformComponent>();
    ecs.RegisterComponent<TextureComponent>();
    ecs.RegisterComponent<AiControllerComponent>();
    ecs.RegisterComponent<SpaceshipComponent>();
    ecs.RegisterComponent<AlienComponent>();
    ecs.RegisterComponent<MysteryshipComponent>();
    ecs.RegisterComponent<BlockComponent>();
    ecs.RegisterComponent<ObstacleComponent>();
    ecs.RegisterComponent<ActiveStateComponent>();
}

void Game::RegisterSystems()
{
    // (updated in order)
    ecs.RegisterSystem<AiUpdateSystem>();
    ecs.RegisterSystem<PlayerUpdateSystem>();
    ecs.RegisterSystem<MysteryshipSpawnSystem>();
    ecs.RegisterSystem<DrawSystem>();
    ecs.RegisterSystem<RenderSystem>();
}

void Game::CreateEntities()
{
    this->GenerateSpaceship();
    this->GenerateAliens();
    this->GenerateMysteryship();
    this->GenerateObstacles();
}

void Game::GenerateSpaceship()
{
    uint64_t spaceshipId = ecs.GetNewEntity();
    ecs.GetComponent<TextureComponent>(spaceshipId)->Texture = LoadTexture("resources/graphics/spaceship.png");
    int spaceshipWidth = ecs.GetComponent<TextureComponent>(spaceshipId)->Texture.width;
    int spaceshipHeight = ecs.GetComponent<TextureComponent>(spaceshipId)->Texture.height;
    float spaceshipX = (GetScreenWidth() - spaceshipWidth) / 2;
    float spaceshipY = (GetScreenHeight() - spaceshipHeight - 100);
    ecs.GetComponent<TransformComponent>(spaceshipId)->Position = {spaceshipX, spaceshipY};
    ecs.GetComponent<TransformComponent>(spaceshipId)->Angle = 0;
    ecs.GetComponent<PlayerInputComponent>(spaceshipId)->LinearSpeed = 5;
    ecs.GetComponent<SpaceshipComponent>(spaceshipId)->ShootSound = LoadSound("resources/sounds/laser.ogg");
    ecs.GetComponent<SpaceshipComponent>(spaceshipId)->LastShootTime = 0.0;
}

void Game::GenerateAliens()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            int type;
            if (i == 0)
            {
                type = 3;
            }
            else if (i < 3)
            {
                type = 2;
            }
            else
            {
                type = 1;
            }
            float x = j * 55 + 75;
            float y = i * 55 + 110;
            uint64_t alienId = ecs.GetNewEntity();
            ecs.GetComponent<TextureComponent>(alienId)->Texture = LoadTexture(("resources/graphics/alien_" + std::to_string(type) + ".png").c_str());
            int alienWidth = ecs.GetComponent<TextureComponent>(alienId)->Texture.width;
            int alienHeight = ecs.GetComponent<TextureComponent>(alienId)->Texture.height;
            ecs.GetComponent<TransformComponent>(alienId)->Position = {x, y};
            ecs.GetComponent<TransformComponent>(alienId)->Angle = 0;
            ecs.GetComponent<AiControllerComponent>(alienId)->Direction = {1, 0};
            ecs.GetComponent<AlienComponent>(alienId)->Type = type;
        }
    }
}

void Game::GenerateMysteryship()
{
    uint64_t mysteryShipId = ecs.GetNewEntity();
    ecs.GetComponent<TextureComponent>(mysteryShipId)->Texture = LoadTexture("resources/graphics/mystery.png");
    int mysteryShipWidth = ecs.GetComponent<TextureComponent>(mysteryShipId)->Texture.width;
    int mysteryShipHeight = ecs.GetComponent<TextureComponent>(mysteryShipId)->Texture.height;
    ecs.GetComponent<TransformComponent>(mysteryShipId)->Position = {0, 90};
    ecs.GetComponent<TransformComponent>(mysteryShipId)->Angle = 0;
    ecs.GetComponent<AiControllerComponent>(mysteryShipId)->Direction = {0, 0};
    ecs.GetComponent<MysteryshipComponent>(mysteryShipId)->Speed = GetRandomValue(1, 3);
    ecs.GetComponent<ActiveStateComponent>(mysteryShipId)->Active = false;
    ecs.GetComponent<MysteryshipComponent>(mysteryShipId)->Timer = 0.0;
    ecs.GetComponent<MysteryshipComponent>(mysteryShipId)->Cooldown = GetRandomValue(10, 20);
}

void Game::GenerateObstacles()
{
    uint64_t obstacleId = ecs.GetNewEntity();
    auto &grid = ecs.GetComponent<ObstacleComponent>(obstacleId)->Grid;

    int obstacleWidth = grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    for (int i = 0; i < 4; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        Vector2 basePosition = {offsetX, float(GetScreenHeight() - 200)};
        for (int j = 0; j < grid.size(); j++)
        {
            for (int k = 0; k < grid[j].size(); k++)
            {
                if (grid[j][k] == 1)
                {
                    uint64_t blockId = ecs.GetNewEntity();
                    ecs.GetComponent<BlockComponent>(blockId)->Size = {3, 3};
                    ecs.GetComponent<BlockComponent>(blockId)->Color = {243, 216, 63, 255};
                    ecs.GetComponent<TransformComponent>(blockId)->Position = {basePosition.x + k * 3, basePosition.y + j * 3};
                }
            }
        }
    }
}

void Game::Update()
{
    // Update the game
    ecs.Update();
}