#include "Game.hpp"
#include "raylib.h"
#include "Components/PlayerInputComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/SpaceshipComponent.hpp"
#include "Systems/DrawSystem.hpp"
#include "Systems/PlayerUpdateSystem.hpp"

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
    ecs.RegisterComponent<SpaceshipComponent>();
}

void Game::RegisterSystems()
{
    ecs.RegisterSystem<PlayerUpdateSystem>();
    ecs.RegisterSystem<DrawSystem>();
}

void Game::CreateEntities()
{
    uint64_t spaceshipId = ecs.GetNewEntity();
    ecs.GetComponent<SpaceshipComponent>(spaceshipId)->Texture = LoadTexture("resources/graphics/spaceship.png");
    int spaceshipWidth = ecs.GetComponent<SpaceshipComponent>(spaceshipId)->Texture.width;
    int spaceshipHeight = ecs.GetComponent<SpaceshipComponent>(spaceshipId)->Texture.height;
    float spaceshipX = (GetScreenWidth() - spaceshipWidth) / 2;
    float spaceshipY = (GetScreenHeight() - spaceshipHeight - 100);
    ecs.GetComponent<TransformComponent>(spaceshipId)->Position = {spaceshipX, spaceshipY};
    ecs.GetComponent<TransformComponent>(spaceshipId)->Angle = 0;
    ecs.GetComponent<PlayerInputComponent>(spaceshipId)->LinearSpeed = 5;
}

void Game::Update()
{
    // Update the game
    ecs.Update();
}