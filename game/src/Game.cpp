#include "Game.hpp"
#include "raylib.h"
#include "patch.hpp"
#include <string>
#include "Components/PlayerInputComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextureComponent.hpp"
#include "Components/AiControllerComponent.hpp"
#include "Systems/DrawSystem.hpp"
#include "Systems/PlayerUpdateSystem.hpp"
#include "Systems/AiUpdateSystem.hpp"

#define _ECS_IMPLEMENTATION
#include "ecs.h"


Game* Game::s_pInstance = 0;
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
}

void Game::RegisterSystems()
{
    // (updated in order)
    ecs.RegisterSystem<AiUpdateSystem>();
    ecs.RegisterSystem<PlayerUpdateSystem>();
    ecs.RegisterSystem<DrawSystem>();
}

void Game::CreateEntities()
{
    this->GenerateSpaceship();
    this->GenerateAliens();
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
            float x = j * 55 +75;
            float y = i * 55 + 110;
            uint64_t alienId = ecs.GetNewEntity();
            ecs.GetComponent<TextureComponent>(alienId)->Texture = LoadTexture(("resources/graphics/alien_" + std::to_string(type) + ".png").c_str());
            int alienWidth = ecs.GetComponent<TextureComponent>(alienId)->Texture.width;
            int alienHeight = ecs.GetComponent<TextureComponent>(alienId)->Texture.height;
            ecs.GetComponent<TransformComponent>(alienId)->Position = {x, y};
            ecs.GetComponent<TransformComponent>(alienId)->Angle = 0;
            ecs.GetComponent<AiControllerComponent>(alienId)->Type = type;
        }

    }
}

void Game::Update()
{
    // Update the game
    ecs.Update();
}